#pragma once
#include "Graph.h"
class ImpulseSignal : public Graph
{
private:
    double m_impulse_position;
    double m_amplitude;

    double m_impulse_position_copy;
    double m_amplitude_copy;

    void overrideOriginalArguments();

public:

    explicit ImpulseSignal(double amplitude, double position, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~ImpulseSignal();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};