#include "TriangularFunction.h"
TriangularFunction::TriangularFunction(double amplitude, double width, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Rectangular_Function, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_amplitude(amplitude), m_width(width), m_shift(shift)
{
    calculateGraphData();
}

TriangularFunction::~TriangularFunction()
{
}

void TriangularFunction::calculateGraphData()
{
    size_t num_samples = static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1);
    m_graph_data = std::vector<double>(num_samples, 0);

    int index_center = static_cast<int>((-m_x_min + m_shift) * m_sample_frequency);
    int index_start = index_center - static_cast<int>((m_width / 2) * m_sample_frequency);
    int index_end = index_center + static_cast<int>((m_width / 2) * m_sample_frequency);

    double k = m_amplitude / (m_width / 2);

    for (int i = std::max(0, index_start); i <= index_center && i < static_cast<int>(num_samples); ++i)
    {
        m_graph_data[i] = k * (i - index_start) / m_sample_frequency;
    }

    for (int i = index_center + 1; i <= index_end && i < static_cast<int>(num_samples); ++i)
    {
        m_graph_data[i] = m_amplitude - k * (i - index_center) / m_sample_frequency;
    }

    saveDataToFile();
}

void TriangularFunction::renderImGuiEditGraph()
{
}
