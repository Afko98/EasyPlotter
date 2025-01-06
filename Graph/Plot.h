#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include "../Graph/GraphTypes/Graph.h"
#include "../gnuplot-iostream.h"
#include "../UseImGui.h"

class Graph;

class Plot
{
	std::vector<Graph*>m_graph_list;
	std::string m_name;
	std::string m_dir_path;

	Gnuplot * gp;

public:
	
	explicit Plot(std::string dir_path, std::string name);
	~Plot();

	const std::vector<Graph*> getGraphList() const { return m_graph_list; }

	void addNewGraph(Graph* g);
	void removeGraph(Graph *g);

	std::string getName() { return m_name; };
	std::string getDirPath() { return m_dir_path; }

	void renderGraphList();

	void linePlot()
	{
		//*gp << "plot '-' using ($0 * " << 1.0 / m_sample_frequency << " + " << m_x_min << "):1 with lines title 'v0'\n";
		//
		//gp->send(m_graph_data);
	}
};
