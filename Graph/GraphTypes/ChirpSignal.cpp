#include "ChirpSignal.h"
ChirpSignal::ChirpSignal(double amplitude, double inital_f, double final_f, double phase_shift, std::string graph_name, double sample_freq, double x_min, double x_max, float line_colour[4], int line_type, std::string label_x, std::string label_y)
    : Graph(GraphType::Chirp_Signal, graph_name, sample_freq, x_min, x_max, line_colour, line_type, label_x, label_y)
{
    m_unique_arg._amplitude = amplitude;
    m_unique_arg._phase_shift = phase_shift;
    m_unique_arg._final_frequency = final_f;
    m_unique_arg._inital_frequency = inital_f;
    copyArgumentsForGui();
    calculateGraphData();
}

ChirpSignal::~ChirpSignal()
{

}

void ChirpSignal::calculateGraphData()
{
    m_graph_data.clear();
    m_graph_data.reserve(static_cast<size_t>((m_base_arg._x_max - m_base_arg._x_min) * m_base_arg._sample_frequency + 1) *1.05);

    double delta_frequency = (m_unique_arg._final_frequency - m_unique_arg._inital_frequency) / ((m_base_arg._x_max - m_base_arg._x_min) * m_base_arg._sample_frequency + 1);
    std::cout << "delta frequency: " << delta_frequency;

    double current_frequency = m_unique_arg._inital_frequency; // Use a local copy
    for (int i = 0; i < (m_base_arg._x_max - m_base_arg._x_min) * m_base_arg._sample_frequency + 1; i++)
    {
        double x = m_base_arg._x_min + (i * (1.0 / m_base_arg._sample_frequency));
        m_graph_data.push_back(std::sin(TWO_PI * current_frequency * x));
        current_frequency += delta_frequency;
    }

    saveDataToFile();
}

void ChirpSignal::renderImGuiEditGraph()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(499, 1)); // Adjust offset
    ImGui::BeginChild(("ChirpSignal##list" + m_base_arg._graph_name).c_str(), ImVec2(windowSize.x - 500, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);
    ImGui::Text(("Selected graph: " + m_base_arg._graph_name).c_str());
    ImGui::Dummy(ImVec2(10, 10));

    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::Text("  f(x) = C");
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_amplitude_copy, 0.1, 10.0);
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Initial Frequency (Hz)", &m_inital_frequency_copy, 0.1, 10.0);
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Final Frequency (Hz)", &m_final_frequency_copy, 0.1, 10.0);
    ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_phase_shift_copy, 0.0, 360.0);

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

void ChirpSignal::copyArgumentsForGui()
{
    strncpy_s(m_graph_name_copy, sizeof(m_graph_name_copy), m_base_arg._graph_name.c_str(), _TRUNCATE);
    strncpy_s(m_label_x_copy, sizeof(m_label_x_copy), m_base_arg._x_label.c_str(), _TRUNCATE);
    strncpy_s(m_label_y_copy, sizeof(m_label_y_copy), m_base_arg._y_label.c_str(), _TRUNCATE);

    m_amplitude_copy = m_unique_arg._amplitude;
    m_phase_shift_copy = m_unique_arg._phase_shift;
    m_inital_frequency_copy = m_unique_arg._inital_frequency;
    m_final_frequency_copy = m_unique_arg._final_frequency;

    m_sample_freq_copy = m_base_arg._sample_frequency;
    m_x_min_copy = m_base_arg._x_min;
    m_x_max_copy = m_base_arg._x_max;
    for (int i = 0; i < 4; ++i)
    {
        m_line_colour_copy[i] = m_base_arg._line_colour[i];
    }
    m_line_type_copy = m_base_arg._line_type;
}

void ChirpSignal::overrideOriginalArguments()
{
    m_base_arg._graph_name = m_graph_name_copy;
    m_base_arg._x_label = m_label_x_copy;
    m_base_arg._y_label = m_label_y_copy;

    m_unique_arg._amplitude = m_amplitude_copy;
    m_unique_arg._phase_shift = m_phase_shift_copy;
    m_unique_arg._inital_frequency = m_inital_frequency_copy;
    m_unique_arg._final_frequency = m_final_frequency_copy;

    m_base_arg._sample_frequency = m_sample_freq_copy;
    m_base_arg._x_min = m_x_min_copy;
    m_base_arg._x_max = m_x_max_copy;
    for (int i = 0; i < 4; ++i)
    {
        m_base_arg._line_colour[i] = m_line_colour_copy[i];
    }
    m_base_arg._line_type = m_line_type_copy;
}
