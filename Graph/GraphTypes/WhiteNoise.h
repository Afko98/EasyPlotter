#pragma once
#include "Graph.h"
class WhiteNoise : public Graph
{
private:
    double m_mean;
    double m_standard_deviation;

public:

    explicit WhiteNoise(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~WhiteNoise();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};