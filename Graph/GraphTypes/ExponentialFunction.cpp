#include "ExponentialFunction.h"
#include <cmath>

ExponentialFunction::ExponentialFunction(double exponent, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Exponential_Function, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_exponent(exponent), m_shift(shift)
{
    calculateGraphData();
}

ExponentialFunction::~ExponentialFunction()
{

}

void ExponentialFunction::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) * 1.05);

    for (double x = m_x_min; x <= m_x_max; x += 1.0 / m_sample_frequency)
    {
        double value = std::exp((x - m_shift) * m_exponent);
        if (std::isinf(value))
            value = std::numeric_limits<double>::max();

        m_graph_data.push_back(value);
    }

    saveDataToFile();
}


void ExponentialFunction::renderImGuiEditGraph()
{

}
