#pragma once

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "../Graph/GraphTypes/CalculatedFunction.h"
#include "../Graph/GraphTypes/Constant.h"
#include "../Graph/GraphTypes/ChirpSignal.h"
#include "../Graph/GraphTypes/Cosine.h"
#include "../Graph/GraphTypes/ExponentialFunction.h"
#include "../Graph/GraphTypes/GaussianFunction.h"
#include "../Graph/GraphTypes/ImpulseSignal.h"
#include "../Graph/GraphTypes/PulseTrain.h"
#include "../Graph/GraphTypes/RectangularFunction.h"
#include "../Graph/GraphTypes/SawtoothWave.h"
#include "../Graph/GraphTypes/SquareWawe.h"
#include "../Graph/GraphTypes/TriangularFunction.h"
#include "../Graph/GraphTypes/TriangularWave.h"
#include "../Graph/GraphTypes/UniformNoise.h"
#include "../Graph/GraphTypes/WhiteNoise.h"

class Plot;

class UseImGui {
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
	static float m_new_color[4];
	static int m_new_linetype;

	static double m_new_generator_amplitude;
	static double m_new_generator_frequency;
	static double m_new_generator_phase_shift;
	static double m_new_generator_width;
	static float m_new_generator_duty_cycle;
	static double m_new_generator_step_time;
	static double m_new_generator_ramp_begin;
	static double m_new_generator_ramp_end;
	static double m_new_generator_slope;
	static double m_new_generator_mean;
	static double m_new_generator_standard_deviation;
	static double m_new_generator_initial_frequency;
	static double m_new_generator_end_frequency;
	static double m_new_generator_min_amplitude;
	static double m_new_generator_max_amplitude;
	static int m_new_generated_signal;

	static void ResetGeneratorParameters();
public:
	void Render();
	static void renderAddNewGraph(Plot *p);
	static void renderAddMathFunction(Plot *p);
	static void renderAddGenerated(Plot *p);
	static void renderAddFromFile(Plot *p);
	static void renderAddFromFileEPFormat(Plot* p);
};