#include "MathFunction.h"
#include <random>

MathFunction::MathFunction(std::string function, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Math_Function, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_function(function)
{
    copyArgumentsForGui();
    calculateGraphData();
}

MathFunction::~MathFunction()
{

}

void MathFunction::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_base_arg._x_max - m_base_arg._x_min) * m_base_arg._sample_frequency + 1) * 1.05);

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    double x = 0;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();  // Includes math constants like pi and e

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;

    for (x = m_base_arg._x_min; x <= m_base_arg._x_max; x+= 1.0/m_base_arg._sample_frequency) 
    {
        m_graph_data.push_back(expression.value());
    }

    saveDataToFile();
}


void MathFunction::renderImGuiEditGraph()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(499, 1)); // Adjust offset
    ImGui::BeginChild(("MathFunction##list" + m_base_arg._graph_name).c_str(), ImVec2(windowSize.x - 500, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);
    ImGui::Text(("  Selected graph: " + m_base_arg._graph_name).c_str());
    ImGui::Dummy(ImVec2(10, 10));

    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::Text(("  f(x) = " + m_function).c_str());
    ImGui::SetNextItemWidth(250.0f); ImGui::InputText("  Function", m_function_copy, sizeof(m_function_copy));

    // Handle the title input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  Sample freq (Hz)", &m_sample_freq_copy, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_min", &m_x_min_copy, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_max", &m_x_max_copy, 0.1, 2.0, "%.4f");

    // Handle the function input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    // ImGui input fields
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Graph name", m_graph_name_copy, sizeof(m_graph_name_copy));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  X label", m_label_x_copy, sizeof(m_label_x_copy));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Y label", m_label_y_copy, sizeof(m_label_y_copy));

    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::ColorEdit4("  Line Color", m_line_colour_copy);

    ImGui::SetNextItemWidth(250.0f);
    ImGui::Combo("  Line Type", &m_line_type_copy, lineTypes, IM_ARRAYSIZE(lineTypes));

    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    bool valid_input = true;
    std::string error_message;

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    double x = 0;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();  // Includes math constants like pi and e

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;

    if (!parser.compile(m_function, expression)) {
        valid_input = false;
        error_message = "Error: Function expression invalid!";
    }

    if (m_x_max_copy < m_x_min_copy) 
    {
        valid_input = false;
        error_message = "Error: x_max cannot be less than x_min.";
    }

    if (m_sample_freq_copy <= 0) 
    {
        valid_input = false;
        error_message = "Error: Sample frequency must be greater than 0.";
    }

    if (strlen(m_graph_name_copy) == 0) 
    {
        valid_input = false;
        error_message = "Error: Graph name cannot be empty.";
    }

    if (!valid_input)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), error_message.c_str());
    }

    ImGui::SetCursorPos(ImVec2(windowSize.x - 640, windowSize.y - 50));
    if (ImGui::Button("  APPLY  "))
    {
        if (valid_input)
        {
            overrideOriginalArguments();
            calculateGraphData();
            copyArgumentsForGui();
        } 
    }

    ImGui::EndChild();
}

void MathFunction::copyArgumentsForGui()
{
    strncpy_s(m_graph_name_copy, sizeof(m_graph_name_copy), m_base_arg._graph_name.c_str(), _TRUNCATE);
    strncpy_s(m_label_x_copy, sizeof(m_label_x_copy), m_base_arg._x_label.c_str(), _TRUNCATE);
    strncpy_s(m_label_y_copy, sizeof(m_label_y_copy), m_base_arg._y_label.c_str(), _TRUNCATE);

    strncpy_s(m_function_copy, sizeof(m_function_copy), m_function.c_str(), _TRUNCATE);

    m_sample_freq_copy = m_base_arg._sample_frequency;
    m_x_min_copy = m_base_arg._x_min;
    m_x_max_copy = m_base_arg._x_max;
    for (int i = 0; i < 4; ++i)
    {
        m_line_colour_copy[i] = m_base_arg._line_colour[i];
    }
    m_line_type_copy = m_base_arg._line_type;
}

void MathFunction::overrideOriginalArguments()
{
    m_base_arg._graph_name = m_graph_name_copy;
    m_base_arg._x_label = m_label_x_copy;
    m_base_arg._y_label = m_label_y_copy;

    m_function = m_function_copy;

    m_base_arg._sample_frequency = m_sample_freq_copy;
    m_base_arg._x_min = m_x_min_copy;
    m_base_arg._x_max = m_x_max_copy;
    for (int i = 0; i < 4; ++i)
    {
        m_base_arg._line_colour[i] = m_line_colour_copy[i];
    }
    m_base_arg._line_type = m_line_type_copy;
}
