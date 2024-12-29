#include "Graph.h"

void Graph::calculateGraphData()
{
    m_graph_data.clear();

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    double x = m_x_min;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();  // Includes constants like pi and e

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    std::string expression_str = m_function;

    if (!parser.compile(expression_str, expression))
    {
        std::cerr << "Error: " << parser.error() << "\n";
        return;
    }

    for (x = m_x_min; x <= m_x_max; x += 1.0 / m_sample_frequency)  // Adjust range and step as needed
    {
        std::cout << x;
        m_graph_data.push_back(expression.value());
    }
}

Graph::Graph(std::string function, std::string title, double freq, double x_min, double x_max, std::string label_x, std::string label_y)
{
    
}

Graph::Graph(std::string file_path)
{
	m_function = file_path;
}

Graph::Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
{
    m_generator_amplitude = 1.0;
    m_generator_frequency = 1.0;
    m_generator_phase_shift = 0.0;
    m_generator_width = 1.0;
    m_generator_duty_cycle = 50.0f;
    m_generator_step_time = 0.0;
    m_generator_ramp_begin = 0.0;
    m_generator_ramp_end = 1.0;
    m_generator_slope = 1.0;
    m_generator_mean = 0.0;
    m_generator_standard_deviation = 1.0;
    m_generator_initial_frequency = 1.0;
    m_generator_end_frequency = 10.0;
    m_generator_min_amplitude = -1.0;
    m_generator_max_amplitude = 1.0;

    m_function = "";
    m_x_max = x_max;
    m_x_min = x_min;
    m_sample_frequency = sample_freq;
    m_graph_name = graph_name;
    m_x_label = label_x;
    m_y_label = label_y;
    m_graph_type = graph_type;

    double range = m_x_max - m_x_min;
    if (range > 0 && m_sample_frequency > 0)
    {
        m_graph_data.reserve(static_cast<std::size_t>(std::round(range * m_sample_frequency * 1.05)));
    }
    else
    {
        throw std::invalid_argument("Invalid range or sample frequency");
    }
}

void Graph::setSampleFrequency(double frequency)
{
    m_sample_frequency = frequency;
}

void Graph::setXMin(double x_min)
{
    m_x_min = x_min;
}

void Graph::setXMax(double x_max)
{
    m_x_max = x_max;
}
