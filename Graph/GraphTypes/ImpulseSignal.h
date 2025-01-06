#pragma once
#include "Graph.h"
class ImpulseSignal : public Graph
{
private:
    double m_impulse_position;
    double m_amplitude;

public:

    explicit ImpulseSignal(double amplitude, double position, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~ImpulseSignal();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};