#include "SquareWawe.h"

SquareWawe::SquareWawe(double amplitude, double frequency, double phase_shift, float duty_cycle, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Square_Wave, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude), m_frequency(frequency), m_duty_cycle(duty_cycle)
{
    m_phase_shift = fmod(phase_shift, 180.0);
    calculateGraphData();
}

SquareWawe::~SquareWawe()
{

}

void SquareWawe::calculateGraphData()
{
    size_t num_samples = static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1);
    m_graph_data = std::vector<double>(num_samples, 0);

    double period = 1.0 / m_frequency;
    double high_duration = m_duty_cycle / 100.0 * period;

    for (size_t i = 0; i < num_samples; ++i)
    {
        double x = m_x_min + i / m_sample_frequency;
        double shifted_x = x + period / 360.0 * m_phase_shift;

        double mod_time = fmod(shifted_x, period);
        if (mod_time < 0) mod_time += period;

        m_graph_data[i] = (mod_time < high_duration) ? m_amplitude : 0; 
    }

    saveDataToFile();
}


void SquareWawe::renderImGuiEditGraph()
{

}
