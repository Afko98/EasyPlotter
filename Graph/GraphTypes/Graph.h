#pragma once
#include "exprtk.hpp"
#include "../gnuplot-iostream.h"
#include <filesystem>
#include "../Plot.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

class Plot;

enum class GraphType {
	Constant,             //0
	Cosine,      //2
	Rectangular_Function, //3
	Square_Wave,          //4
	Triangular_Function,  //5
	Triangular_Wave,      //6
	Sawtooth_Wave,        //7
	Step_Function,        //8
	Sgn_Function,         //9
	Impulse_Signal,       //10
	Pulse_Train,          //11
	Ramp_Function,        //12
	Exponential_Function, //13
	Gaussian_Function,    //14
	Chirp_Signal,         //15
	White_Noise,          //16
	Uniform_Noise,
	Math_Function,
	From_File,
	From_File_EP_Format,
	Calculated_Function
};

static const double PI = 3.141592653589793238463;
static const double TWO_PI = 2 * PI;

enum class LineType 
{
	Solid, 
	Dashed, 
	Dotted, 
	DashDot
};

struct GraphArg
{
	std::string _graph_name = "";  
	std::string _x_label = "";     
	std::string _y_label = "";     
	GraphType _graph_type = GraphType::Calculated_Function;  
	double _sample_frequency = 0.0; 
	double _x_min = 0.0;          
	double _x_max = 10.0;         
	float _line_colour[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	int _line_type = 0;
};

class Graph
{
protected:
	GraphArg m_base_arg;
	Plot* m_parent;
	std::vector<double> m_graph_data;
	
	static const char* lineTypes[4];

	bool saveDataToFile();

	char m_graph_name_copy[256] = { 0 };
	char m_label_x_copy[256] = { 0 };
	char m_label_y_copy[256] = { 0 };

	double m_sample_freq_copy;
	double m_x_min_copy;
	double m_x_max_copy;
	float m_line_colour_copy[4] = { 0 };
	int m_line_type_copy;

private:
	Gnuplot* gp;

public:
	Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
	virtual ~Graph() = 0;

	std::string getGraphName() { return m_base_arg._graph_name; }
	void setGraphName(std::string name) { m_base_arg._graph_name = name; }

	std::string getXLabel() { return m_base_arg._x_label; }
	void setXLabel(std::string x_label) { m_base_arg._x_label = x_label; }

	std::string getYLabel() { return m_base_arg.m_base_arg._y_label; }
	void setYLabel(std::string y_label) { m_base_arg.m_base_arg._y_label = y_label; }

	double getSamleFrequency() { return m_base_arg._sample_frequency; }
	void setSampleFrequency(double frequency);

	double getXMin() { return m_base_arg._x_min; }
	void setXMin(double x_min);

	double getXMax() { return m_base_arg._x_max; }
	void setXMax(double x_max);

	int getGraphSize() { return m_graph_data.size(); }

	std::vector<double> getGraphData();

	GraphType getGraphType() { return m_base_arg._graph_type; }
	void setGraphType(GraphType graph_type) { m_base_arg._graph_type = graph_type; }

	void setParent(Plot* parent);

	void plotGraph();
	virtual void calculateGraphData() = 0;
	virtual void renderImGuiEditGraph() = 0;
	virtual void copyArgumentsForGui() = 0;

	void renderCalculateGraph();

	void calculateIntegral();

	//	add friend functions for calculating operations with 2 graphs;
	//	add member functions for calculating ingeral, diferencial... single graph operations;
};

