#pragma once
#include "Graph.h"
class RectangularFunction : public Graph
{
private:
    double m_amplitude;
    double m_width;
    double m_shift;

public:

    explicit RectangularFunction(double amplitude, double width, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~RectangularFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};

