#pragma once
#include "Graph.h"
class GaussianFunction : public Graph
{
private:
    double m_mean;
    double m_standard_deviation;

public:

    explicit GaussianFunction(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~GaussianFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};