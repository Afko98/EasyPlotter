#pragma once
#include <vector>
#include "Plot.h"

class Plot;
class Graph;

class PlotContainer
{
	static PlotContainer *m_instance;
	PlotContainer() {};
	
	std::vector<Plot *> m_plot_list;

public:
	static PlotContainer* instance();

	const std::vector<Plot*> getPlotList() const { return m_plot_list; }

	void addPlot(std::string dir_path, std::string name) { m_plot_list.push_back(new Plot(dir_path, name)); }; // do check first if Plot was created...
	void removePlot(Plot* p);

	void renderPlotList();
};

