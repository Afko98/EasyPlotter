#include "Constant.h"

Constant::Constant(double amplitude, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
    : Graph(GraphType::Constant, graph_name, sample_freq, x_min, x_max, label_x, label_y), m_amplitude(amplitude)
{
    calculateGraphData();
}

Constant::~Constant()
{

}

void Constant::calculateGraphData()
{
    m_graph_data = std::vector<double>(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1), m_amplitude);
    saveDataToFile();
}


void Constant::renderImGuiEditGraph()
{
    
}
