#include "Graph.h"

const char* Graph::lineTypes[4] = { "Solid", "Dashed", "Dotted", "Dash-Dot" };

bool Graph::saveDataToFile()
{
    if (!m_parent || m_parent->getDirPath() == "")
        return false;
    std::ofstream dataFile(m_parent->getDirPath() + "\\" + m_graph_name + ".epd", std::ios::binary); // Open the file in binary mode

    if (!dataFile.is_open()) {
        std::cerr << m_parent->getDirPath() + "\\" + m_graph_name + ".epd" << std::endl;
        return false;
    }

    // Write the y values to the binary file
    for (const auto& y : m_graph_data) {
        dataFile.write(reinterpret_cast<const char*>(&y), sizeof(double));
    }

    dataFile.close(); // Close the file
    m_graph_data.clear();
    m_graph_data.shrink_to_fit();
    return true;
}

Graph::Graph(GraphType graph_type, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
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
    m_parent = nullptr;
    for (int i = 0; i < 4; ++i) 
    {
        m_line_colour[i] = line_colour[i];
    }
    m_line_type = line_type;
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

std::vector<double> Graph::getGraphData()  // reading from file...
{
    std::vector<double> data;

    if (!m_parent)
        return m_graph_data;

    std::ifstream data_file(m_parent->getDirPath() + "\\" + m_graph_name + ".epd", std::ios::binary);
    if (!data_file.is_open())
    {
        std::cerr << "Failed to open file for reading: " << m_graph_name + ".epd" << std::endl;
        return std::vector<double>();
    }

    data_file.seekg(0, std::ios::end);
    size_t file_size = data_file.tellg();
    size_t num_el = file_size / sizeof(double);

    data.resize(num_el);

    data_file.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num_el; ++i)
    {
        data_file.read(reinterpret_cast<char*>(&data[i]), sizeof(double));
    }

    data_file.close();
    return data;

}

void Graph::setParent(Plot* parent)
{     
    if (m_parent)
    {
        m_parent = parent;
        calculateGraphData();
    }
    else
    {
        m_parent = parent;
        saveDataToFile();
    }
}

void Graph::plotGraph() {

    //if has parent load from file, if not load directly from variable
    *gp << "set autoscale yfix\n";
*gp << "set offset 0, 0, 0.1, 0.1\n"; 
    *gp << "plot '" << m_parent->getDirPath() + "\\" + m_graph_name + ".epd"
        << "' binary format='%double' using ($0 * " << 1.0 / m_sample_frequency << " + " << m_x_min
        << "):1 with lines title '" << m_graph_name << "'\n";

    //*gp << "plot '" << m_parent->getDirPath() + "\\" + m_graph_name + ".epd" << "' binary format='%double' using ($0 * " << 1.0/m_sample_frequency << " + " << m_x_min << "):1 with lines title '"<< m_graph_name <<"'\n";
    gp->flush();  // Ensure the command is sent
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Optional: Give Gnuplot time to render
}

void Graph::calculateIntegral()
{

}
