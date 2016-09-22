#include <math.h>
#include <stdlib.h>
#include "../Headers/sine_body.h"

auto Hippocrates::Tests::Sine::SineBody::Reset() -> void {
	datasetsTested = 0;
	fitness = 0;
};

auto Hippocrates::Tests::Sine::SineBody::Update(const std::vector<float>& networkOutputs) -> void {
	auto distanceToCorrectResult = abs(sin(currentDataSet) - networkOutputs[0]);
	fitness += 100 - ( distanceToCorrectResult * 50 );

	datasetsTested++;
};

auto Hippocrates::Tests::Sine::SineBody::ProvideNetworkWithInputs() const -> std::vector<float> {
	auto LO = -M_PI;
	auto HI = M_PI;

	currentDataSet = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(HI-LO)));

	return { currentDataSet };
};
