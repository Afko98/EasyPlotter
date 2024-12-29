#include "UseImGui.h"
#include "./Graph/Graph.h"
#include <iostream>
#include "Graph/GraphContainer.h"

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
}
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

void UseImGui::renderPlotController()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(1, 1)); // Adjust offset
    ImGui::BeginChild("Plot selector", ImVec2(250, windowSize.y-2), true, ImGuiWindowFlags_NoMove);

    ImGui::Text("Plot selector");

    ImGui::EndChild();
}

void UseImGui::renderGraphController()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(250, 1)); // Adjust offset
    ImGui::BeginChild("Graph selector", ImVec2(250, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);

    ImGui::Text("Graph selector");

    ImGui::EndChild();
}

void UseImGui::renderAddNewGraph()
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
            renderAddMathFunction();
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
            renderAddGenerated();
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
            renderAddFromFile();
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
            renderAddFromFileEPFormat();
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

void UseImGui::renderAddMathFunction()
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
        // Handle graph addition
    }
}

void UseImGui::renderAddGenerated()
{
    ImGui::Dummy(ImVec2(0, 15));
    ImGui::SetNextItemWidth(250.0f);
    const char* signalOptions[] = {
        "Constant",             //0
        "A*sin(2πft + φ)",      //1
        "A*cos(2πft + φ)",      //2
        "Rectangular Function", //3
        "Square Wave",          //4
        "Triangular Function",  //5
        "Triangular Wave",      //6
        "Sawtooth Wave",        //7
        "Step Function",        //8
        "Sgn Function",         //9
        "Impulse Signal",       //10
        "Pulse Train",          //11
        "Ramp Function",        //12
        "Exponential Function", //13
        "Gaussian Function",    //14
        "Chirp Signal",         //15
        "White Noise",          //16
        "Uniform Noise"         //17
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
    case 2: 
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f);
        ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        break;
    case 3: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  width", &m_new_generator_width, 0.1, 2.0);
        break;
    case 4: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::SliderFloat("  Duty cycle", &m_new_generator_duty_cycle, 0.0f, 100.0f);
        break;
    case 5:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  width", &m_new_generator_width, 0.1, 2.0);
        break;

    case 6:  
    case 7:   
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);
        break;
    case 8:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, -10.0f, 10.0f);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Step Position", &m_new_generator_step_time, -10.0f, 10.0f);
        break;

    case 9: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Amplitude", &m_new_generator_amplitude, -10.0f, 10.0f);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Step Position", &m_new_generator_step_time, -10.0f, 10.0f);
        break;
    case 10: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Impulse Position", &m_new_generator_step_time, -10.0f, 10.0f);
        break;

    case 11:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Frequency/step (Hz)", &m_new_generator_frequency, 0.1, 10.0);
        break;

    case 12: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  RampBegin", &m_new_generator_ramp_begin, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  RampEnd", &m_new_generator_ramp_end, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Slope k (as in xk+n)", &m_new_generator_slope, 0.1, 10.0);
        break;

    case 13:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  t (e^xt)", &m_new_generator_amplitude, 0.1, 2.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.1, 2.0);
        break;

    case 14:
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Mean", &m_new_generator_mean, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Standard deviation", &m_new_generator_standard_deviation, 0.0, 360.0);
        if (m_new_generator_standard_deviation < 0.0) {
            m_new_generator_standard_deviation = 0.0;
        }
        break;

    case 15: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Initial Frequency (Hz)", &m_new_generator_initial_frequency, 0.1, 10.0); 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Final Frequency (Hz)", &m_new_generator_end_frequency, 0.1, 10.0);     
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Phase Shift (degrees)", &m_new_generator_phase_shift, 0.0, 360.0);      
        break;

    case 16: 
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Mean", &m_new_generator_mean, 0.1, 10.0);
        ImGui::SetNextItemWidth(250.0f); ImGui::InputDouble("  Standard deviation", &m_new_generator_standard_deviation, 0.0, 360.0);
        break;

    case 17: 
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

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui::SetCursorPos(ImVec2(windowSize.x - 640, windowSize.y - 50));
    if (ImGui::Button("  ADD GRAPH  "))
    {
        // Handle graph addition
    }
}

void UseImGui::renderAddFromFile()
{
    ImGui::Button("ADD GRAPH");
}

void UseImGui::renderAddFromFileEPFormat()
{
    ImGui::Button("ADD GRAPH");
}

void UseImGui::Render() {
    static float f = 0.0f;
    static int counter = 0;
    

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
    ImGui::Begin("EasyPlot", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse);

    renderPlotController();
    renderGraphController();
    renderAddNewGraph();

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

  
    ImGui::End();
}

