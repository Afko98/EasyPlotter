#include "WhiteNoise.h"
#include <random>

WhiteNoise::WhiteNoise(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::White_Noise, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_mean(mean), m_standard_deviation(standard_deviation)
{
    calculateGraphData();
}

WhiteNoise::~WhiteNoise()
{

}

void WhiteNoise::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) * 1.05);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(m_mean, m_standard_deviation);

    for (int i = 0; i < static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1); i++)
    {
        m_graph_data.push_back(dist(gen));
    }

    saveDataToFile();
}


void WhiteNoise::renderImGuiEditGraph()
{

}
