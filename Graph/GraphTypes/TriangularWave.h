#pragma once
#include "Graph.h"
class TriangularWave : public Graph
{
private:
    double m_amplitude;
    double m_frequency;
    double m_phase_shift;

public:

    explicit TriangularWave(double amplitude, double frequency, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x = "", std::string label_y = "");
    ~TriangularWave();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
};