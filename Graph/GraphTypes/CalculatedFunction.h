#pragma once
#include "Graph.h"
class CalculatedFunction : public Graph
{
private:

    void overrideOriginalArguments();

public:

    explicit CalculatedFunction(std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~CalculatedFunction();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};