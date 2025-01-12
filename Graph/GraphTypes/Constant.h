#ifndef CONSTANT_H
#define CONSTANT_H

// Class definition
#include "./Graph.h"


class Constant : public Graph
{
private:
    double m_amplitude;
    double m_amplitude_copy;

    void overrideOriginalArguments();

public:

    explicit Constant(double amplitude, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x = "", std::string label_y = "");
    ~Constant();

    void calculateGraphData() override;
    void renderImGuiEditGraph() override;
    void copyArgumentsForGui() override;
};

#endif // CONSTANT_H