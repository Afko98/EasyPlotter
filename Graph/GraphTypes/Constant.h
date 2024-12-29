#pragma once
#include "Graph.h"

class Constant : public Graph
{
private:
    double m_amplitude;

public:

    explicit Constant(GraphType graph_type, double amplitude, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~Constant();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};
