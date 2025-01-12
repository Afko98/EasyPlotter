#pragma once
#include "Graph.h"
class WhiteNoise : public Graph
{
private:
    double m_mean;
    double m_standard_deviation;


    // used for ImGui
    double m_mean_copy;
    double m_standard_deviation_copy;

    void overrideOriginalArguments();

public:

    explicit WhiteNoise(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~WhiteNoise();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};