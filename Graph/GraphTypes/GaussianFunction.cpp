#include "GaussianFunction.h"
#include <random>

GaussianFunction::GaussianFunction(double mean, double standard_deviation, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::White_Noise, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_mean(mean), m_standard_deviation(standard_deviation)
{
    calculateGraphData();
}

GaussianFunction::~GaussianFunction()
{

}

void GaussianFunction::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) * 1.05);

    const double inv_sqrt_2pi = 1.0 / std::sqrt(2.0 * PI);
    const double variance = m_standard_deviation * m_standard_deviation;
    const double coeff = inv_sqrt_2pi / m_standard_deviation;

    for (double x = m_x_min; x <= m_x_max; x += 1.0 / m_sample_frequency) 
    {
        double diff = x - m_mean;
        double exponent = -(diff * diff) / (2.0 * variance);
        m_graph_data.push_back(coeff * std::exp(exponent));
    }

    saveDataToFile();
}


void GaussianFunction::renderImGuiEditGraph()
{

}
