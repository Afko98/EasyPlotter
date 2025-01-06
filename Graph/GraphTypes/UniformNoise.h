#pragma once
#include "Graph.h"
class UniformNoise : public Graph
{
private:
    double m_y_min;
    double m_y_max;

public:

    explicit UniformNoise(double y_min, double y_max, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~UniformNoise();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};