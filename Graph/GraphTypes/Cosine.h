#pragma once
#include "Graph.h"
class Cosine : public Graph
{
private:
    double m_amplitude;
    double m_frequency;
    double m_phase_shift;

    double m_amplitude_copy;
    double m_frequency_copy;
    double m_phase_shift_copy;

    void overrideOriginalArguments();

public:

    explicit Cosine(double amplitude, double frequency, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~Cosine();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};

