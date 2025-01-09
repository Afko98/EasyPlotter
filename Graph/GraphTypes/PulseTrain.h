#pragma once
#include "Graph.h"
class PulseTrain : public Graph
{
private:
    double m_frequency;
    double m_amplitude;

public:

    explicit PulseTrain(double amplitude, double frequency, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~PulseTrain();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};
