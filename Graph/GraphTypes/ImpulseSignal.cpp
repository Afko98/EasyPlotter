#include "ImpulseSignal.h"
ImpulseSignal::ImpulseSignal(double amplitude, double position, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Impulse_Signal, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude), m_impulse_position(position)
{
    calculateGraphData();
}

ImpulseSignal::~ImpulseSignal()
{
}

void ImpulseSignal::calculateGraphData()
{
    m_graph_data = std::vector<double>(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1), 0);
    int index_impulse_position = static_cast<int>((-m_x_min + m_impulse_position) * m_sample_frequency);

    if (index_impulse_position >= 0 && index_impulse_position < m_graph_data.size())
        m_graph_data[index_impulse_position] = m_amplitude;

    saveDataToFile();
}

void ImpulseSignal::renderImGuiEditGraph()
{
}