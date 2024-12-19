#pragma once
#include <vector>
#include "Graph.h"

class GraphContainer
{
	std::vector<Graph *> m_graph_container;
	GraphContainer();
	static GraphContainer* m_instance;
	Graph* m_selected_graph = nullptr;

public:
	
	std::vector<Graph*>getGraphs() { return m_graph_container; }
	static GraphContainer* instance();

	void addNewGraph(std::string function, std::string title, double freq = 0.1, double x_min = -10, double x_max = 10, std::string label_x = "x", std::string label_y = "f(x)");
	void deleteGraph(Graph* g);
	void selectedGraph(Graph* g);

	Graph* getSelectedGraph() { return m_selected_graph; }
};

