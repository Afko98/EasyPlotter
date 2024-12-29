#include "Cosine.h"
#include <chrono>
Cosine::Cosine(GraphType graph_type, double amplitude, double frequency, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Cosine, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude), m_frequency(frequency), m_phase_shift(phase_shift)
{
    calculateGraphData();
}

Cosine::~Cosine()
{

}

void Cosine::calculateGraphData()
{
    auto start = std::chrono::high_resolution_clock::now(); // Start time
    double period = 1.0 / m_frequency;
    double sample_period = 1.0 / m_sample_frequency;

    m_graph_data.reserve(static_cast<size_t>(((m_x_max - m_x_min) * m_sample_frequency) + 1) * 1.05);
    
    for (double x = m_x_min; x <= m_x_max; x += sample_period)
    {
        m_graph_data.push_back(std::cos(TWO_PI * m_frequency * x + m_phase_shift));
    }
    //if (1.1 / m_frequency > m_x_max - m_x_min)
    //{
    //    for (double x = m_x_min; x <= m_x_max; x += sample_period)
    //    {
    //        m_graph_data.push_back(std::cos(TWO_PI * m_frequency * x + m_phase_shift));
    //    }
    //    return;
    //}
    //
    //std::vector<double>one_period;
    //one_period.reserve(static_cast<size_t>((1.0 / m_frequency * m_sample_frequency) + 1) * 1.1);
    //
    //for (double x = m_x_min; x < m_x_min + period; x += sample_period)
    //{
    //    one_period.push_back(m_amplitude * std::cos(TWO_PI * m_frequency * x + m_phase_shift));
    //}
    //
    //std::cout << static_cast<size_t>((m_x_max - m_x_min) / period);
    //for (int i = 0; i < static_cast<size_t>((m_x_max - m_x_min) / period); i++)  // adding values for whole periods
    //{
    //    for (const double &value : one_period)
    //    {
    //        m_graph_data.push_back(value);
    //    }
    //}
    //
    //std::cout << std::endl;
    //std::cout << ((m_x_max - m_x_min) / period);
    //std::cout << std::endl;
    //std::cout << static_cast<size_t>((m_x_max - m_x_min) / period);
    //std::cout << std::endl;
    //std::cout << "left samples" << static_cast<size_t>((((m_x_max - m_x_min) / period) - (static_cast<int>((m_x_max - m_x_min) / period))) * one_period.size());
    //for (int i = 0; i <= static_cast<size_t>((   ((m_x_max - m_x_min) / period) - (static_cast<int>((m_x_max - m_x_min) / period))) * one_period.size()); i++)  // adding values for whole periods
    //{
    //    m_graph_data.push_back(one_period[i]);
    //}
    auto end = std::chrono::high_resolution_clock::now(); // End time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Calculate duration

    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

}


void Cosine::renderImGuiEditGraph()
{

}
