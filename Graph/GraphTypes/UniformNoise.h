#pragma once
#include "Graph.h"
class UniformNoise : public Graph
{
private:
    double m_y_min;
    double m_y_max;

    double m_y_min_copy;
    double m_y_max_copy;

    void overrideOriginalArguments();

public:

    explicit UniformNoise(double y_min, double y_max, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~UniformNoise();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};