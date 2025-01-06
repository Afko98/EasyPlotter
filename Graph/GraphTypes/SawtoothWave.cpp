#include "SawtoothWave.h"
SawtoothWave::SawtoothWave(double amplitude, double frequency, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Sawtooth_Wave, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude), m_phase_shift(phase_shift), m_frequency(frequency)
{
    calculateGraphData();
}

SawtoothWave::~SawtoothWave()
{

}

void SawtoothWave::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) * 1.05);

    double period = 1.0 / m_frequency;
    double phase_offset = m_phase_shift / 360.0 * period; 

    double k = m_amplitude / (1.0 / m_frequency / 2);

    for (double x = m_x_min; x <= m_x_max; x += 1.0/m_sample_frequency) 
    {
        double normalized_x = fmod((x - phase_offset), period); 
        if (normalized_x < 0) {
            normalized_x += period; 
        }

            m_graph_data.push_back(normalized_x * k);
    }

    saveDataToFile();
}


void SawtoothWave::renderImGuiEditGraph()
{

}
