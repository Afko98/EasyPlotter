#include "Graph.h"


Graph::Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, std::string label_x, std::string label_y)
{
    double range = x_max - x_min;
    if (range <= 0 && sample_freq <= 0)
    {
        throw std::invalid_argument("Invalid range or sample frequency");
    }

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path gnuplotPath = currentPath / "gnuplot" / "bin" / "gnuplot.exe";
    std::string pathStr = gnuplotPath.string();

    std::string escapedPath;
    for (char ch : pathStr) {
        if (ch == '\\') {
            escapedPath += '\\';  // Add an extra backslash
        }
        escapedPath += ch;
    }
    escapedPath = "\"" + escapedPath + "\"";
    std::cout << "Path is " << escapedPath;
    gp = new Gnuplot(escapedPath);

    m_x_max = x_max+0.0000000001;
    m_x_min = x_min;
    m_sample_frequency = sample_freq;
    m_graph_name = graph_name;
    m_x_label = label_x;
    m_y_label = label_y;
    m_graph_type = graph_type;
}

Graph::~Graph() {
    // Empty implementation or cleanup code if needed
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

void Graph::plotGraph()
{
    *gp << "plot '-' using ($0 * " << 1.0 / m_sample_frequency << " + " << m_x_min << "):1 with lines title 'v0'\n";

    gp->send(m_graph_data);
}
