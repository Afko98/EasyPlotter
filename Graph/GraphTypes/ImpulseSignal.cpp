#include "ImpulseSignal.h"
ImpulseSignal::ImpulseSignal(double amplitude, double position, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Impulse_Signal, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y), m_amplitude(amplitude), m_impulse_position(position)
{
    copyArgumentsForGui();
    calculateGraphData();
}

ImpulseSignal::~ImpulseSignal()
{
}

void ImpulseSignal::calculateGraphData()
{
    m_graph_data = std::vector<double>(static_cast<size_t>((m_x_max - m_x_min) * m_sample_frequency + 1), 0);
    int index_impulse_position = static_cast<int>((-m_x_min + m_impulse_position) * m_sample_frequency);

    if (index_impulse_position >= 0 && index_impulse_position < m_graph_data.size())
        m_graph_data[index_impulse_position] = m_amplitude;

    saveDataToFile();
}


void ImpulseSignal::renderImGuiEditGraph()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(499, 1)); // Adjust offset
    ImGui::BeginChild(("ImpulseSignal##list" + m_graph_name).c_str(), ImVec2(windowSize.x - 500, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);
    ImGui::Text(("Selected graph: " + m_graph_name).c_str());
    ImGui::Dummy(ImVec2(10, 10));

    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::Text("  f(x) = d(A, position)");
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_amplitude_copy, 0.1, 10.0);
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Impulse Position", &m_impulse_position_copy, -10.0f, 10.0f);

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

void ImpulseSignal::copyArgumentsForGui()
{
    strncpy_s(m_graph_name_copy, sizeof(m_graph_name_copy), m_graph_name.c_str(), _TRUNCATE);
    strncpy_s(m_label_x_copy, sizeof(m_label_x_copy), m_x_label.c_str(), _TRUNCATE);
    strncpy_s(m_label_y_copy, sizeof(m_label_y_copy), m_y_label.c_str(), _TRUNCATE);

    m_amplitude_copy = m_amplitude;
    m_impulse_position_copy = m_impulse_position;

    m_sample_freq_copy = m_sample_frequency;
    m_x_min_copy = m_x_min;
    m_x_max_copy = m_x_max;
    for (int i = 0; i < 4; ++i)
    {
        m_line_colour_copy[i] = m_line_colour[i];
    }
    m_line_type_copy = m_line_type;
}

void ImpulseSignal::overrideOriginalArguments()
{
    m_graph_name = m_graph_name_copy;
    m_x_label = m_label_x_copy;
    m_y_label = m_label_y_copy;

    m_amplitude = m_amplitude_copy;
    m_impulse_position = m_impulse_position_copy;

    m_sample_frequency = m_sample_freq_copy;
    m_x_min = m_x_min_copy;
    m_x_max = m_x_max_copy;
    for (int i = 0; i < 4; ++i)
    {
        m_line_colour[i] = m_line_colour_copy[i];
    }
    m_line_type = m_line_type_copy;
}
