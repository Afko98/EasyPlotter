#pragma once
#include "Graph.h"
struct ChirpArg {
    double _inital_frequency;
    double _final_frequency;
    double _phase_shift;
    double _amplitude;
};

class ChirpSignal : public Graph
{
private:
    ChirpArg m_unique_arg;

    double m_inital_frequency_copy;
    double m_final_frequency_copy;
    double m_phase_shift_copy;
    double m_amplitude_copy;

    void overrideOriginalArguments();

public:

    explicit ChirpSignal(double amplitude, double inital_f, double final_f, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~ChirpSignal();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};
