#include "PlotContainer.h"

PlotContainer* PlotContainer::m_instance = nullptr;
Plot* PlotContainer::m_selected_plot = nullptr;

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
    ImGui::SetCursorPos(ImVec2(1, 1)); // Adjust offset
    ImGui::BeginChild("Plot selector", ImVec2(250, windowSize.y - 2), true, ImGuiWindowFlags_NoMove);

    ImGui::Spacing();
    ImGui::SetCursorPos(ImVec2(50, 12)); // Adjust offset
    if (ImGui::Button("Add New Plot", ImVec2(150, 36)))
    {
        ImGui::OpenPopup("AddNewPlot");
    }
    if (ImGui::BeginPopup("AddNewPlot"))
    {
        ImGui::Text("Add new plot");

        static char dir[256] = {};
        static char name[256] = {};
        ImGui::InputText("##Directory", dir, IM_ARRAYSIZE(dir));
        ImGui::SameLine();
        if (ImGui::Button("Select Directory"))
        {
            IGFD::FileDialogConfig config;
            config.path = "";
            ImGuiFileDialog::Instance()->OpenDialog(
                "ChooseDir",                      
                "Select Directory",               
                nullptr,
                config
            );
        }
        if (ImGuiFileDialog::Instance()->Display("ChooseDir", 32, ImVec2(350, 500)))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string selectedPath = ImGuiFileDialog::Instance()->GetCurrentPath();
                strncpy_s(dir, selectedPath.c_str(), IM_ARRAYSIZE(dir) - 1); 
                dir[IM_ARRAYSIZE(dir) - 1] = '\0'; 
            }
            ImGuiFileDialog::Instance()->Close();
        }
        ImGui::InputText("  Plot name", name, IM_ARRAYSIZE(name));

        ImGui::Dummy(ImVec2(0,10));

        if (ImGui::Button("Add", ImVec2(70, 26)))
        {
            PlotContainer::instance()->addPlot(dir, name);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Close", ImVec2(70, 26)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    ImGui::EndChild();


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
        if (ImGui::Button(("  Select  ##" + p->getName()).c_str(), ImVec2(102, 25)))
        {
            m_selected_plot = p;
        }

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

    if (m_selected_plot)
    {
        m_selected_plot->renderGraphList();
    }
}
