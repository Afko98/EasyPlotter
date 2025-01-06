#include "PlotContainer.h"

PlotContainer* PlotContainer::m_instance = nullptr;

PlotContainer* PlotContainer::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new PlotContainer();
	}
	return m_instance;
}

void PlotContainer::removePlot(Plot* p)
{
	auto it = std::find(m_plot_list.begin(), m_plot_list.end(), p);

	if (it != m_plot_list.end())
	{
		delete* it;
		m_plot_list.erase(it);
	}
}

void PlotContainer::renderPlotList()
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Set position for the right-aligned box
    ImGui::SetCursorPos(ImVec2(1, 60)); // Adjust offset
    ImGui::BeginChild("Plot selector##list", ImVec2(250, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);
    ImGui::Text("Plot List:");
    ImGui::Dummy(ImVec2(10, 10));

    for (auto p : m_plot_list)
    {
        ImGui::BeginChild(("Plot selector##" + p->getName()).c_str(), ImVec2(230, 100), true, ImGuiWindowFlags_NoMove);
        ImGui::Text(("Plot: " + p->getName()).c_str());

        ImGui::Dummy(ImVec2(10, 0));
        
        ImGui::Button(("  Plot  ##" + p->getName()).c_str(), ImVec2(102, 25));
        ImGui::SameLine();
        ImGui::Button(("  Select  ##" + p->getName()).c_str(), ImVec2(102, 25));

        ImGui::Button(("  Remove  ##" + p->getName()).c_str(), ImVec2(102, 25));
        ImGui::SameLine();
        if (ImGui::Button("Dir", ImVec2(102, 25)))
        {
            ImGui::OpenPopup("FullTextPopup");
        }

        if (ImGui::BeginPopup("FullTextPopup"))
        {
            ImGui::Text(p->getDirPath().c_str());
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(10, 5));
    }

    ImGui::EndChild();
}
