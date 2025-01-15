#pragma once
#include "Graph.h"
class MathFunction : public Graph
{
private:
    std::string m_function;


    // used for ImGui
    char m_function_copy[256] = { 0 };

    void overrideOriginalArguments();

public:

    explicit MathFunction(std::string function, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~MathFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};