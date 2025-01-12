#pragma once
#include "Graph.h"
class ExponentialFunction : public Graph
{
private:
    double m_exponent;
    double m_shift;

    double m_exponent_copy;
    double m_shift_copy;

    void overrideOriginalArguments();

public:

    explicit ExponentialFunction(double exponent, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~ExponentialFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};