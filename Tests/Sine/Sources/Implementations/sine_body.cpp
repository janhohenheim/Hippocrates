#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include "../Headers/sine_body.h"
#include <cmath>

auto Hippocrates::Tests::Sine::SineBody::Reset() -> void {
	datasetsTested = 0;
	fitness = 0;
};

auto Hippocrates::Tests::Sine::SineBody::Update(const std::vector<float>& networkOutputs) -> void {
	auto distanceToCorrectResult = abs(sin(currentDataSet) - networkOutputs[0]);
	fitness += 100.0f - ( distanceToCorrectResult * 50.0f );

	datasetsTested++;
};

auto Hippocrates::Tests::Sine::SineBody::ProvideNetworkWithInputs() const -> std::vector<float> {
	static auto RandomFloat = [](float a, float b)    {
		auto random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		auto diff = b - a;
		auto r = random * diff;
		return a + r;
	};

	currentDataSet = RandomFloat(-M_PI, M_PI);

	return {currentDataSet / static_cast<float>(M_PI)};
};
