#include "GraphContainer.h"

GraphContainer* GraphContainer::m_instance = nullptr;

GraphContainer::GraphContainer()
{
	
}

void GraphContainer::addNewGraph(std::string function, std::string title, double freq, double x_min, double x_max, std::string label_x, std::string label_y)
{
	Graph* graph = new Graph(function, title, freq, x_min, x_max, label_x, label_y);
	m_graph_container.push_back(graph);
	m_selected_graph = graph;
}

void GraphContainer::deleteGraph(Graph* g)
{
	m_selected_graph = nullptr;
	for (int i = 0; i < m_graph_container.size(); i++)
	{
		if (m_graph_container[i]->getTitle() == g->getTitle())
		{
			m_graph_container.erase(m_graph_container.begin() + i);
			delete g;
			return;
		}
	}
}

GraphContainer* GraphContainer::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GraphContainer();
	}
	return m_instance;
}

void GraphContainer::selectedGraph(Graph *g)
{
	m_selected_graph = g;  // Update m_selected_graph
}
