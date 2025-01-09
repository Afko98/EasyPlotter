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

    char m_graph_name_copy[256] = { 0 };
    char m_label_x_copy[256] = { 0 };
    char m_label_y_copy[256] = { 0 };

    double m_sample_freq_copy;
    double m_x_min_copy;
    double m_x_max_copy;
    float m_line_colour_copy[4] = { 0 };
    int m_line_type_copy;

    void overrideOriginalArguments();

public:

    explicit WhiteNoise(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~WhiteNoise();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};