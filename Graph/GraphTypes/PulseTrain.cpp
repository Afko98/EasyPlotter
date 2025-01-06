#include "PulseTrain.h"
PulseTrain::PulseTrain(double amplitude, double frequency, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Pulse_Train, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude), m_frequency(frequency)
{
    calculateGraphData();
}

PulseTrain::~PulseTrain()
{
}

void PulseTrain::calculateGraphData()
{
    m_graph_data = std::vector<double>(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1), 0);
    int index_step = static_cast<int> (1.0 / m_frequency * m_sample_frequency);
    std::cout << index_step;
    for (int i = 0; i < static_cast<int>(m_graph_data.size()); i += index_step)
    {
        m_graph_data[i] = m_amplitude;
    }

    saveDataToFile();
}

void PulseTrain::renderImGuiEditGraph()
{
}