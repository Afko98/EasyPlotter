#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include "../gnuplot-iostream.h"

class Plotter
{
protected:
	std::string m_function, m_title, m_x_label, m_y_label;
	std::vector<double> m_graph_data;
	double m_sample_frequency;
	double m_x_min, m_x_max;

private:
	Gnuplot * gp;

public:
	
	Plotter();  // Constructor declaration

	void linePlot()
	{
		if (m_graph_data.empty())
			return;

		*gp << "plot '-' using ($0 * " << 1.0 / m_sample_frequency << " + " << m_x_min << "):1 with lines title 'v0'\n";

		gp->send(m_graph_data);
	}
};

