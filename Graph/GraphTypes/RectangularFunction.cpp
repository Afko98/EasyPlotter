#include "RectangularFunction.h"

RectangularFunction::RectangularFunction(double amplitude, double width, double shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
	: Graph(GraphType::Rectangular_Function, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_amplitude(amplitude), m_width(width), m_shift(shift)
{
    calculateGraphData();
}

RectangularFunction::~RectangularFunction()
{
}

void RectangularFunction::calculateGraphData()
{
    m_graph_data = std::vector<double>(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1), 0);
    int index_center = static_cast<int>((-m_x_min) * m_sample_frequency);

    int index_start = index_center - static_cast<int>((m_width / 2) * m_sample_frequency);
    int index_end = index_center + static_cast<int>((m_width / 2) * m_sample_frequency);

    index_start = std::max(index_start, 0);
    index_end = std::min(index_end, static_cast<int>(m_graph_data.size()) - 1);

    for (int i = index_start; i <= index_end; ++i)
    {
        m_graph_data[i] = 1;
    }

    saveDataToFile();
}

void RectangularFunction::renderImGuiEditGraph()
{
}
