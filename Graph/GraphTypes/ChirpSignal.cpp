#include "ChirpSignal.h"
ChirpSignal::ChirpSignal(double amplitude, double inital_f, double final_f, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Chirp_Signal, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_amplitude(amplitude), m_phase_shift(phase_shift), m_inital_frequency(inital_f), m_final_frequency(final_f)
{
    calculateGraphData();
}

ChirpSignal::~ChirpSignal()
{

}

void ChirpSignal::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1) *1.05);

    double delta_frequency = (m_final_frequency - m_inital_frequency) / ((m_x_max - m_x_min) * m_sample_frequency + 1);
    std::cout << "delta frequency: " << delta_frequency;

    double current_frequency = m_inital_frequency; // Use a local copy
    for (int i = 0; i < (m_x_max - m_x_min) * m_sample_frequency + 1; i++)
    {
        double x = m_x_min + (i * (1.0 / m_sample_frequency));
        m_graph_data.push_back(std::sin(TWO_PI * current_frequency * x));
        current_frequency += delta_frequency;
    }

    saveDataToFile();
}


void ChirpSignal::renderImGuiEditGraph()
{

}
