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
    m_function = function;
    m_x_max = x_max;
    m_x_min = x_min;
    m_sample_frequency = freq;
    m_title = title;
    m_x_label = label_x;
    m_y_label = label_y;
    std::cout << "adding new graph " << function << " " << title << " " << freq << " " << x_min << " " << x_max << " " << label_x << " " << label_y;
    calculateGraphData();
}

Graph::Graph(std::string file_path)
{
	m_function = file_path;
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
