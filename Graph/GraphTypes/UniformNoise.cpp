#include "UniformNoise.h"
#include <random>

UniformNoise::UniformNoise(double y_min, double y_max, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Uniform_Noise, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_y_min(y_min), m_y_max(y_max)
{
    calculateGraphData();
}

UniformNoise::~UniformNoise()
{

}

void UniformNoise::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) * 1.05);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(m_y_min, m_y_max);

    for (int i = 0; i < static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1); i++)
    {
        m_graph_data.push_back(dist(gen));
    }

    saveDataToFile();
}


void UniformNoise::renderImGuiEditGraph()
{

}
