#pragma once
#include "Plotter.h"
#include "exprtk.hpp"

class Graph : public Plotter
{
	

public:
	Graph(std::string function, std::string title, double freq, double x_min, double x_max, std::string label_x, std::string label_y);
	Graph(std::string file_path);

	std::string getTitle() { return m_title; }
	void setTitle(std::string title) { m_title = title; }

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

	void calculateGraphData();
};

