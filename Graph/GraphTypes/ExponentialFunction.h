#pragma once
#include "Graph.h"
class ExponentialFunction : public Graph
{
private:
    double m_exponent;
    double m_shift;

public:

    explicit ExponentialFunction(double exponent, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~ExponentialFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};