#pragma once
#include "Graph.h"
class TriangularFunction : public Graph
{
private:
    double m_amplitude;
    double m_width;
    double m_shift;

public:

    explicit TriangularFunction(double amplitude, double width, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~TriangularFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};
