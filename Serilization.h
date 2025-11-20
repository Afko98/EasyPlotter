#pragma once
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
#include "../Graph/GraphTypes/MathFunction.h"

class Serilization
{
public:
	static void saveConfig();
	static Graph* loadConfig();
};

