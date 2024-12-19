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

void UseImGui::Render() {
    static float f = 0.0f;
    static int counter = 0;
    

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
    ImGui::Begin("EasyPlot", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

    

    ImGui::Dummy(ImVec2(5.0f, 10.0f));
    if (ImGui::Button("Add new\n graph", ImVec2(95.0f, 80.0f)))
    {
        m_new_graph_open = true;
    }// Buttons return true when clicked (most widgets return true when edited/activated)

  // Move to the same line as the label
    
        
    

    if (m_new_graph_open)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
        ImGui::BeginDisabled(); // Disable interactions with other windows
    }

    // Render other windows
    renderFunctionWindow();
    if (GraphContainer::instance()->getSelectedGraph())
        renderSelectedGraphInfo();

    if (m_new_graph_open)
    {
        ImGui::EndDisabled();
        ImGui::PopStyleVar();
        renderNewGraphMaker(); // Ensure this is still interactive
    }
                // Adjust box size


  
    ImGui::End();
}

