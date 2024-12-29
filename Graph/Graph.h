#pragma once
#include "Plotter.h"
#include "exprtk.hpp"

enum class GraphType {
	Constant,             //0
	sin,      //1
	cos,      //2
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
	From_File_EP_Format
};

class Graph
{
	std::string m_function, m_graph_name, m_x_label, m_y_label;
	std::vector<double> m_graph_data;
	GraphType m_graph_type;
	double m_sample_frequency;
	double m_x_min, m_x_max;

	double m_generator_amplitude;
	double m_generator_frequency;
	double m_generator_phase_shift;
	double m_generator_width;
	float  m_generator_duty_cycle;
	double m_generator_step_time;
	double m_generator_ramp_begin;
	double m_generator_ramp_end;
	double m_generator_slope;
	double m_generator_mean;
	double m_generator_standard_deviation;
	double m_generator_initial_frequency;
	double m_generator_end_frequency;
	double m_generator_min_amplitude;
	double m_generator_max_amplitude;

public:
	Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");

	std::string getGraphName() { return m_graph_name; }
	void setGraphName(std::string name) { m_graph_name = name; }

	std::string getFunction() { return m_function; }

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

	double getGeneratorAmplitude() { return m_generator_amplitude; }
	void setGeneratorAmplitude(double amplitude) { m_generator_amplitude = amplitude; }

	double getGeneratorFrequency() { return m_generator_frequency; }
	void setGeneratorFrequency(double frequency) { m_generator_frequency = frequency; }

	double getGeneratorPhaseShift() { return m_generator_phase_shift; }
	void setGeneratorPhaseShift(double phase_shift) { m_generator_phase_shift = phase_shift; }

	double getGeneratorWidth() { return m_generator_width; }
	void setGeneratorWidth(double width) { m_generator_width = width; }

	float getGeneratorDutyCycle() { return m_generator_duty_cycle; }
	void setGeneratorDutyCycle(float duty_cycle) { m_generator_duty_cycle = duty_cycle; }

	double getGeneratorStepTime() { return m_generator_step_time; }
	void setGeneratorStepTime(double step_time) { m_generator_step_time = step_time; }

	double getGeneratorRampBegin() { return m_generator_ramp_begin; }
	void setGeneratorRampBegin(double ramp_begin) { m_generator_ramp_begin = ramp_begin; }

	double getGeneratorRampEnd() { return m_generator_ramp_end; }
	void setGeneratorRampEnd(double ramp_end) { m_generator_ramp_end = ramp_end; }

	double getGeneratorSlope() { return m_generator_slope; }
	void setGeneratorSlope(double slope) { m_generator_slope = slope; }

	double getGeneratorMean() { return m_generator_mean; }
	void setGeneratorMean(double mean) { m_generator_mean = mean; }

	double getGeneratorStandardDeviation() { return m_generator_standard_deviation; }
	void setGeneratorStandardDeviation(double standard_deviation) { m_generator_standard_deviation = standard_deviation; }

	double getGeneratorInitialFrequency() { return m_generator_initial_frequency; }
	void setGeneratorInitialFrequency(double initial_frequency) { m_generator_initial_frequency = initial_frequency; }

	double getGeneratorEndFrequency() { return m_generator_end_frequency; }
	void setGeneratorEndFrequency(double end_frequency) { m_generator_end_frequency = end_frequency; }

	double getGeneratorMinAmplitude() { return m_generator_min_amplitude; }
	void setGeneratorMinAmplitude(double min_amplitude) { m_generator_min_amplitude = min_amplitude; }

	double getGeneratorMaxAmplitude() { return m_generator_max_amplitude; }
	void setGeneratorMaxAmplitude(double max_amplitude) { m_generator_max_amplitude = max_amplitude; }

	GraphType getGraphType() { return m_graph_type; }
	void setGraphType(GraphType graph_type) { m_graph_type = graph_type; }

	void calculateGraphData();
};

