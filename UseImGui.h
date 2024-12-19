#pragma once

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

class UseImGui {
 
	void renderFunctionWindow();
	void renderSelectedGraphInfo();
	void renderNewGraphMaker();

	static char m_selected_function[128];  // Allocate a fixed-size buffer and initialize it
	static char m_selected_title[128];
	static char m_selected_label_x[128];
	static char m_selected_label_y[128];
	static double m_selected_freq, m_selected_x_min, m_selected_x_max;
	static bool m_new_graph_open;

	static char m_new_function[128];  // Allocate a fixed-size buffer and initialize it
	static char m_new_title[128];
	static char m_new_label_x[128];
	static char m_new_label_y[128];
	static double m_new_freq, m_new_x_min, m_new_x_max;

public:
	void Render();
};