#include "Plot.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>

//Plot::Plot()
//{
//    // Get the current directory where the executable is located
//    std::filesystem::path currentPath = std::filesystem::current_path();
//
//    // Build the relative path to gnuplot.exe
//    std::filesystem::path gnuplotPath = currentPath / "gnuplot" / "bin" / "gnuplot.exe";
//
//    // Convert the path to string
//    std::string pathStr = gnuplotPath.string();
//
//    // Escape backslashes in the path for Windows format
//    std::string escapedPath;
//    for (char ch : pathStr) {
//        if (ch == '\\') {
//            escapedPath += '\\';  // Add an extra backslash
//        }
//        escapedPath += ch;
//    }
//
//    // Add quotes around the path
//    escapedPath = "\"" + escapedPath + "\"";
//    std::cout << "Path is " << escapedPath;
//
//    // Initialize the Gnuplot object with the escaped path
//    gp = new Gnuplot(escapedPath);
//}

Plot::Plot(std::string dir_path, std::string name) : m_name(name), m_dir_path(dir_path)
{
    if (!std::filesystem::exists(m_dir_path))
    {
        if (!std::filesystem::create_directories(m_dir_path))
        {
            throw std::runtime_error("Failed to create directory: " + m_dir_path);
        }
    }
    else
    {
        //dir already exists, check files
    }
}

Plot::~Plot()
{
    for (Graph* g : m_graph_list)
    {
        delete g;
    }
    m_graph_list.clear();
}

void Plot::addNewGraph(Graph* g)
{
    m_graph_list.push_back(g); 
    g->setParent(this);
}

void Plot::removeGraph(Graph* g)
{
    auto it = std::find(m_graph_list.begin(), m_graph_list.end(), g);

    if (it != m_graph_list.end())
    {
        delete* it;
        m_graph_list.erase(it);
    }
}

void Plot::renderGraphList()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(250, 60)); // Adjust offset
    ImGui::BeginChild("Graph selector##list", ImVec2(250, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);
    ImGui::Text("Graph List:");
    ImGui::Dummy(ImVec2(10, 10));
    
    for (auto g : m_graph_list)
    {
        ImGui::BeginChild(("Graph selector##" + g->getGraphName()).c_str(), ImVec2(230, 75), true, ImGuiWindowFlags_NoMove);
        ImGui::Text(("Graph: " + g->getGraphName()).c_str());
        ImGui::Dummy(ImVec2(10, 0));
        if (ImGui::Button(("  Plot  ##" + g->getGraphName()).c_str(), ImVec2(102, 25))) {
            g->plotGraph();
        }
        ImGui::SameLine();
        ImGui::Button(("  Option  ##" + g->getGraphName()).c_str(), ImVec2(102, 25));

        ImGui::EndChild();
        ImGui::Dummy(ImVec2(10, 5));
    }
    
    ImGui::EndChild();
}
