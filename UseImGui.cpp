#include "UseImGui.h"
#include <iostream>
#include "../Graph/Plot.h"

char UseImGui::m_selected_function[128] = ""; // Initializing the buffer with an empty string
char UseImGui::m_selected_title[128] = "";
char UseImGui::m_selected_label_x[128] = "";
char UseImGui::m_selected_label_y[128] = "";
double UseImGui::m_selected_freq = 0.0;
double UseImGui::m_selected_x_min = 0.0;
double UseImGui::m_selected_x_max = 0.0;
bool UseImGui::m_new_graph_open = false;

char UseImGui::m_new_function[128] = "sin(x)/x"; // Initializing the buffer with an empty string
char UseImGui::m_new_title[128] = "Sa(x)";
char UseImGui::m_new_label_x[128] = "x";
char UseImGui::m_new_label_y[128] = "f(x)";
double UseImGui::m_new_freq = 5.0;
double UseImGui::m_new_x_min = -20.0;
double UseImGui::m_new_x_max = 20.0;

double UseImGui::m_new_generator_amplitude = 1.0;          
double UseImGui::m_new_generator_frequency = 1.0;          
double UseImGui::m_new_generator_phase_shift = 0.0;        
double UseImGui::m_new_generator_width = 1.0;              
float UseImGui::m_new_generator_duty_cycle = 50.0f;        
double UseImGui::m_new_generator_step_time = 0.0;          
double UseImGui::m_new_generator_ramp_begin = 0.0;         
double UseImGui::m_new_generator_ramp_end = 1.0;          
double UseImGui::m_new_generator_slope = 1.0;              
double UseImGui::m_new_generator_mean = 0.0;               
double UseImGui::m_new_generator_standard_deviation = 1.0; 
double UseImGui::m_new_generator_initial_frequency = 1.0;  
double UseImGui::m_new_generator_end_frequency = 10.0;     
double UseImGui::m_new_generator_min_amplitude = -1.0;    
double UseImGui::m_new_generator_max_amplitude = 1.0;

float UseImGui::m_new_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
int UseImGui::m_new_linetype = 0;
int UseImGui::m_new_generated_signal = 0; // Default to the first signal

void UseImGui::ResetGeneratorParameters() {
    m_new_generator_amplitude = 1.0;
    m_new_generator_frequency = 1.0;
    m_new_generator_phase_shift = 0.0;
    m_new_generator_width = 1.0;
    m_new_generator_duty_cycle = 50.0f;
    m_new_generator_step_time = 0.0;
    m_new_generator_ramp_begin = 0.0;
    m_new_generator_ramp_end = 1.0;
    m_new_generator_slope = 1.0;
    m_new_generator_mean = 0.0;
    m_new_generator_standard_deviation = 1.0;
    m_new_generator_initial_frequency = 1.0;
    m_new_generator_end_frequency = 10.0;
    m_new_generator_min_amplitude = -1.0;
    m_new_generator_max_amplitude = 1.0;
}
/*
void UseImGui::renderFunctionWindow()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(windowSize.x - 290.0f, 20.0f)); // Adjust offset
    ImGui::BeginChild("Functions", ImVec2(273.0f, windowSize.y - 40.0f), true, ImGuiWindowFlags_NoMove);

    // Create a box for buttons

    // Get the graph titles from the GraphContainer
    int i = 0;
    for (auto graph : GraphContainer::instance()->getGraphs())
    {
        ImGui::Text("%s", graph->getTitle());

        std::string deleteButtonLabel = "Delete##" + std::to_string(i); 
        if (ImGui::Button(deleteButtonLabel.c_str(), ImVec2(80.0f, 0.0f)))
        {
            GraphContainer::instance()->deleteGraph(graph);
            break;
        }

        ImGui::SameLine();

        std::string selectButtonLabel = "Select##" + std::to_string(i); 
        if (ImGui::Button(selectButtonLabel.c_str(), ImVec2(80.0f, 0.0f)))
        {
            GraphContainer::instance()->selectedGraph(graph);
            Graph *selected_graph = GraphContainer::instance()->getSelectedGraph();

            if (selected_graph)
            {
                std::copy(selected_graph->getFunction().begin(), selected_graph->getFunction().end(), UseImGui::m_selected_function);
                UseImGui::m_selected_function[selected_graph->getFunction().size()] = '\0';

                std::copy(selected_graph->getTitle().begin(), selected_graph->getTitle().end(), UseImGui::m_selected_title);
                UseImGui::m_selected_title[selected_graph->getTitle().size()] = '\0';

                std::copy(selected_graph->getXLabel().begin(), selected_graph->getXLabel().end(), UseImGui::m_selected_label_x);
                UseImGui::m_selected_label_x[selected_graph->getXLabel().size()] = '\0';

                std::copy(selected_graph->getYLabel().begin(), selected_graph->getYLabel().end(), UseImGui::m_selected_label_y);
                UseImGui::m_selected_label_y[selected_graph->getYLabel().size()] = '\0';

                m_selected_freq = selected_graph->getSamleFrequency();
                m_selected_x_min = selected_graph->getXMin();
                m_selected_x_max = selected_graph->getXMax();
            }
        }

        ImGui::SameLine();

        std::string plotButtonLabel = "Plot##" + std::to_string(i);
        if (ImGui::Button(plotButtonLabel.c_str(), ImVec2(80.0f, 0.0f)))
        {
            graph->linePlot();
        }
        ImGui::Dummy(ImVec2(0, 15));
        i++;
    }
    ImGui::EndChild();
}*/
/*
void UseImGui::renderSelectedGraphInfo()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(5.0f, 120.0f)); // Adjust offset
    ImGui::BeginChild("Selected graph", ImVec2(460.0f, 420.0f), true, ImGuiWindowFlags_NoMove);

    auto selectedGraph = GraphContainer::instance()->getSelectedGraph();
    if (selectedGraph)
    {
        ImGui::Dummy(ImVec2(0, 10));
        ImGui::Text("function: %s", selectedGraph->getFunction().c_str());

        // Handle the title input
        ImGui::Dummy(ImVec2(0, 10));
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputText("Graph title", m_selected_title, IM_ARRAYSIZE(m_selected_title));
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputText("X label", m_selected_label_x, IM_ARRAYSIZE(m_selected_label_x));
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputText("Y label", m_selected_label_y, IM_ARRAYSIZE(m_selected_label_y));

        // Handle the function input
        ImGui::Dummy(ImVec2(0, 10));

        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputDouble("Sample freq (Hz)", &m_selected_freq, 0.1, 2.0, "%.4f");
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputDouble("x_min", &m_selected_x_min, 0.1, 2.0, "%.4f");
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputDouble("x_max double", &m_selected_x_max, 0.1, 2.0, "%.4f");

        
        ImVec2 available_region = ImGui::GetContentRegionAvail();
        ImVec2 button_position(390, 380); // Adjust based on button size

        ImGui::SetCursorPos(button_position);

        if (ImGui::Button("APPLY"))
        {
            selectedGraph->setTitle(m_selected_title);
            selectedGraph->setSampleFrequency(m_selected_freq);
            selectedGraph->setXLabel(m_selected_label_x);
            selectedGraph->setYLabel(m_selected_label_y);
            selectedGraph->setXMax(m_selected_x_max);
            selectedGraph->setXMin(m_selected_x_min);

            selectedGraph->calculateGraphData();
        }

    }
    ImGui::EndChild();
}
*/
/*
void UseImGui::renderNewGraphMaker()
{
    ImGui::SetNextWindowPos(ImVec2(100.0, 100.0));
    ImGui::Begin("Add new graph", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Dummy(ImVec2(0, 10));
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("f(x)", m_new_function, IM_ARRAYSIZE(m_new_function));

    // Handle the title input
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("Graph title", m_new_title, IM_ARRAYSIZE(m_new_title));
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("X label", m_new_label_x, IM_ARRAYSIZE(m_new_label_x));
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("Y label", m_new_label_y, IM_ARRAYSIZE(m_new_label_y));

    // Handle the function input
    ImGui::Dummy(ImVec2(0, 10));

    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputDouble("Sample freq (Hz)", &m_new_freq, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputDouble("x_min", &m_new_x_min, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputDouble("x_max", &m_new_x_max, 0.1, 2.0, "%.4f");

    ImGui::SetCursorPos(ImVec2(300, 360));

    if (ImGui::Button(" ADD "))
    {
        GraphContainer::instance()->addNewGraph(m_new_function, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_label_x, m_new_label_y);
        m_new_graph_open = false;
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL"))
    {
        m_new_graph_open = false;
        ImGui::CloseCurrentPopup();
    }

    ImGui::End();
}
*/

void UseImGui::renderAddNewGraph(Plot* p)
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(499, 1)); // Adjust offset
    ImGui::BeginChild("Add new graph", ImVec2(windowSize.x-500, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);

    ImGui::Text("Add new graph");
    ImGui::Dummy(ImVec2(480, 20));
    if (ImGui::BeginTabBar("MyTabBar")) {
        // Tab 1
        ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(10, 10, 10, 255));        // Inactive
        ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(64, 64, 64, 255)); // Hovered
        ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(74, 100, 130, 255));
        if (ImGui::BeginTabItem("  Math function  ")) {
            ImGui::PopStyleColor(3); // Pop the tab colors
            renderAddMathFunction(p);
            ImGui::EndTabItem();
        }
        else {
            ImGui::PopStyleColor(3); // Ensure colors are popped even if tab isn't selected
        }

        // Tab 2
        ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(10, 10, 10, 255));         // Inactive
        ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(64, 64, 64, 255)); // Hovered
        ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(74, 100, 130, 255));
        if (ImGui::BeginTabItem("  Generator  ")) {
            ImGui::PopStyleColor(3);
            renderAddGenerated(p);
            ImGui::EndTabItem();
        }
        else {
            ImGui::PopStyleColor(3);
        }

        // Tab 3
        ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(10, 10, 10, 255));         // Inactive
        ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(64, 64, 64, 255)); // Hovered
        ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(74, 100, 130, 255));
        if (ImGui::BeginTabItem("  From file  ")) {
            ImGui::PopStyleColor(3);
            renderAddFromFile(p);
            ImGui::EndTabItem();
        }
        else {
            ImGui::PopStyleColor(3);
        }

        ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(10, 10, 10, 255));         // Inactive
        ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(64, 64, 64, 255)); // Hovered
        ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(74, 100, 130, 255));
        if (ImGui::BeginTabItem("  From file (EP format)  ")) {
            ImGui::PopStyleColor(3);
            renderAddFromFileEPFormat(p);
            ImGui::EndTabItem();
        }
        else {
            ImGui::PopStyleColor(3);
        }

        // End the TabBar
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}

void UseImGui::renderAddMathFunction(Plot* p)
{
    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  f(x)", m_new_function, IM_ARRAYSIZE(m_new_function));

    // Handle the title input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  Sample freq (Hz)", &m_new_freq, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_min", &m_new_x_min, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_max", &m_new_x_max, 0.1, 2.0, "%.4f");

    // Handle the function input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Graph name", m_new_title, IM_ARRAYSIZE(m_new_title));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  X label", m_new_label_x, IM_ARRAYSIZE(m_new_label_x));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Y label", m_new_label_y, IM_ARRAYSIZE(m_new_label_y));

    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::ColorEdit4("  Line Color", m_new_color);
    const char* lineTypes[] = { "Solid", "Dashed", "Dotted", "Dash-Dot" };

    ImGui::SetNextItemWidth(250.0f);
    if (ImGui::Combo("  Line Type", &m_new_linetype, lineTypes, IM_ARRAYSIZE(lineTypes))) {
        // Optional: Handle changes, e.g., update preview or log changes
    }

    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui::SetCursorPos(ImVec2(windowSize.x - 640, windowSize.y - 50));
    if (ImGui::Button("  ADD GRAPH  "))
    {
        

        p->closeAddNewGraphWindow();
    }
}

void UseImGui::renderAddGenerated(Plot* p)
{
    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    const char* signalOptions[] = {
        "Constant",             //0
        "A*cos(2πft + φ)",      //1  TODO phase from deg to rad
        "Rectangular Function", //2
        "Square Wave",          //3
        "Triangular Function",  //4
        "Triangular Wave",      //5
        "Sawtooth Wave",        //6
        "Impulse Signal",       //7
        "Pulse Train",          //8
        "Exponential Function", //9
        "Gaussian Function",    //10
        "Chirp Signal",         //11
        "White Noise",          //12
        "Uniform Noise"         //13
        // TODO: Add modulations...
    };

    // Dropdown selector
    
    ImGui::Combo("Select Signal", &m_new_generated_signal, signalOptions, IM_ARRAYSIZE(signalOptions));
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    switch (m_new_generated_signal) {
    case 0: 
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 2.0);
        break;
    case 1: 
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        break;
    case 2: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  width", &m_new_generator_width, 0.1, 2.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Shift", &m_new_generator_phase_shift, 0.0, 2.0);
        break;
    case 3: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::SliderFloat("  Duty cycle", &m_new_generator_duty_cycle, 0.0f, 100.0f);
        break;
    case 4:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  width", &m_new_generator_width, 0.1, 2.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Shift", &m_new_generator_phase_shift, 0.0, 2.0);
        break;

    case 5:  
    case 6:   
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        break;
    case 7: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Impulse Position", &m_new_generator_step_time, -10.0f, 10.0f);
        break;

    case 8:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency/step (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        break;

    case 9:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  t (e^xt)", &m_new_generator_amplitude, 0.1, 2.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Shift", &m_new_generator_phase_shift, 0.1, 2.0);
        break;

    case 10:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Mean", &m_new_generator_mean, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Standard deviation", &m_new_generator_standard_deviation, 0.0, 360.0);
        if (m_new_generator_standard_deviation < 0.0) {
            m_new_generator_standard_deviation = 0.0;
        }
        break;

    case 11: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Initial Frequency (Hz)", &m_new_generator_initial_frequency, 0.1, 10.0); 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Final Frequency (Hz)", &m_new_generator_end_frequency, 0.1, 10.0);     
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);      
        break;

    case 12: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Mean", &m_new_generator_mean, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Standard deviation", &m_new_generator_standard_deviation, 0.0, 360.0);
        break;

    case 13: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Minimum Value", &m_new_generator_min_amplitude, -10.0, 10.0);       
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Maximum Value", &m_new_generator_max_amplitude, -10.0, 10.0);
        break;
    default:
        break;
    }

    // Handle the function input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  Sample freq (Hz)", &m_new_freq, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_min", &m_new_x_min, 0.1, 2.0, "%.4f");
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputDouble("  x_max", &m_new_x_max, 0.1, 2.0, "%.4f");;

    // Handle the title input
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Graph name", m_new_title, IM_ARRAYSIZE(m_new_title));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  X label", m_new_label_x, IM_ARRAYSIZE(m_new_label_x));
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputText("  Y label", m_new_label_y, IM_ARRAYSIZE(m_new_label_y));

    
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::SetNextItemWidth(250.0f);
    ImGui::ColorEdit4("  Line Color", m_new_color);
    const char* lineTypes[] = { "Solid", "Dashed", "Dotted", "Dash-Dot" };

    ImGui::SetNextItemWidth(250.0f);
    if (ImGui::Combo("  Line Type", &m_new_linetype, lineTypes, IM_ARRAYSIZE(lineTypes))) {
        // Optional: Handle changes, e.g., update preview or log changes
    }

    ImGui::Dummy(ImVec2(0, 8));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));

    bool invalid_input = false;
    if (strlen(m_new_title) == 0 || std::find_if(p->getGraphList().begin(), p->getGraphList().end(), [](Graph* g) { return g->getGraphName() == m_new_title; }) != p->getGraphList().end())
    {
        invalid_input = true;
        if (strlen(m_new_title) == 0)
            ImGui::TextColored(ImVec4(0.90f, 0.0f, 0.0f, 1.0f), "Invalid name input!");
        else
            ImGui::TextColored(ImVec4(0.90f, 0.0f, 0.0f, 1.0f), "Graph already added!");
    }

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui::SetCursorPos(ImVec2(windowSize.x - 640, windowSize.y - 50));
    if (ImGui::Button("  ADD GRAPH  "))
    {
        if (invalid_input)
            return;

        switch (m_new_generated_signal) {
        case 0:
            p->addNewGraph(new Constant(m_new_generator_amplitude, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 1:
            p->addNewGraph(new Cosine(m_new_generator_amplitude, m_new_generator_frequency, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 2:
            p->addNewGraph(new RectangularFunction(m_new_generator_amplitude, m_new_generator_width, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 3:
            p->addNewGraph(new SquareWawe(m_new_generator_amplitude, m_new_generator_frequency, m_new_generator_phase_shift, m_new_generator_duty_cycle, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 4:
            p->addNewGraph(new TriangularFunction(m_new_generator_amplitude, m_new_generator_width, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 5:
            p->addNewGraph(new TriangularWave(m_new_generator_amplitude, m_new_generator_frequency, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 6:
            p->addNewGraph(new SawtoothWave(m_new_generator_amplitude, m_new_generator_frequency, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 7:
            p->addNewGraph(new ImpulseSignal(m_new_generator_amplitude, m_new_generator_step_time, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 8:
            p->addNewGraph(new PulseTrain(m_new_generator_amplitude, m_new_generator_frequency, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 9:
            p->addNewGraph(new ExponentialFunction(m_new_generator_amplitude, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 10:
            p->addNewGraph(new GaussianFunction(m_new_generator_mean, m_new_generator_standard_deviation, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 11:
            p->addNewGraph(new ChirpSignal(m_new_generator_amplitude, m_new_generator_initial_frequency, m_new_generator_end_frequency, m_new_generator_phase_shift, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 12:
            p->addNewGraph(new WhiteNoise(m_new_generator_mean, m_new_generator_standard_deviation, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        case 13:
            p->addNewGraph(new UniformNoise(m_new_generator_min_amplitude, m_new_generator_max_amplitude, m_new_title, m_new_freq, m_new_x_min, m_new_x_max, m_new_color, m_new_linetype, m_new_label_x, m_new_label_y));
            break;
        default:
            break;
        }
        p->closeAddNewGraphWindow();
    }
}

void UseImGui::renderAddFromFile(Plot* p)
{
    ImGui::Button("ADD GRAPH");

    p->closeAddNewGraphWindow();
}

void UseImGui::renderAddFromFileEPFormat(Plot* p)
{
    ImGui::Button("ADD GRAPH");

    p->closeAddNewGraphWindow();
}

void UseImGui::Render() {
    static float f = 0.0f;
    static int counter = 0;
    
    //renderAddNewGraph();

    //ImGui::Dummy(ImVec2(5.0f, 10.0f));
    //if (ImGui::Button("Add new\n graph", ImVec2(95.0f, 80.0f)))
    //{
    //    m_new_graph_open = true;
    //}// Buttons return true when clicked (most widgets return true when edited/activated)
    //
  //// Move to the same line as the label
    //
    //    
    //
    //
    //if (m_new_graph_open)
    //{
    //    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
    //    ImGui::BeginDisabled(); // Disable interactions with other windows
    //}
    //
    //// Render other windows
    //renderFunctionWindow();
    //if (GraphContainer::instance()->getSelectedGraph())
    //    renderSelectedGraphInfo();
    //
    //if (m_new_graph_open)
    //{
    //    ImGui::EndDisabled();
    //    ImGui::PopStyleVar();
    //    renderNewGraphMaker(); // Ensure this is still interactive
    //}
    //            // Adjust box size
    //

  
    
}

