#pragma once
#include "exprtk.hpp"
#include "../gnuplot-iostream.h"
#include <filesystem>
#include "../Graph/Plot.h"

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

enum class LineType {
	Solid, 
	Dashed, 
	Dotted, 
	DashDot
};

class Graph
{
protected:
	std::string m_graph_name, m_x_label, m_y_label;
	std::vector<double> m_graph_data;
	GraphType m_graph_type;
	double m_sample_frequency;
	double m_x_min, m_x_max;
	Plot* m_parent;

	float m_line_colour[4];
	int m_line_type;
	static const char* lineTypes[4];

	bool saveDataToFile();

private:
	Gnuplot* gp;

public:
	Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
	virtual ~Graph() = 0;

	std::string getGraphName() { return m_graph_name; }
	void setGraphName(std::string name) { m_graph_name = name; }

	std::string getXLabel() { return m_x_label; }
	void setXLabel(std::string x_label) { m_x_label = x_label; }

	std::string getYLabel() { return m_y_label; }
	void setYLabel(std::string y_label) { m_y_label = y_label; }

	double getSamleFrequency() { return m_sample_frequency; }
	void setSampleFrequency(double frequency);

	double getXMin() { return m_x_min; }
	void setXMin(double x_min);

	double getXMax() { return m_x_max; }
	void setXMax(double x_max);

	int getGraphSize() { return m_graph_data.size(); }

	std::vector<double> getGraphData();

	GraphType getGraphType() { return m_graph_type; }
	void setGraphType(GraphType graph_type) { m_graph_type = graph_type; }

	void setParent(Plot* parent);

	void plotGraph();
	virtual void calculateGraphData() = 0;
	virtual void renderImGuiEditGraph() = 0;
	virtual void copyArgumentsForGui() = 0;

	void calculateIntegral();

	//	add friend functions for calculating operations with 2 graphs;
	//	add member functions for calculating ingeral, diferencial... single graph operations;
};

