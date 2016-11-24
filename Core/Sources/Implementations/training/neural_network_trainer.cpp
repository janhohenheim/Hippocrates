#include "training/neural_network_trainer.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Training;

auto NeuralNetworkTrainer::TrainUnsupervised(SpeciesManager::Bodies& bodies) -> Trained::NeuralNetwork {
	if (loggingEnabled) {
		logger.CreateLoggingDirs();
	}
	species.CreateInitialOrganisms(bodies);
	species.LetGenerationLive();

	generationsPassed = 0;
	auto* champ = &species.GetFittestOrganism();
	while (champ->GetOrCalculateRawFitness() < (champ->GetMaxFitness() - 1e-6)) {
		TrainGenerationAndLogUsingBodies(bodies);
		champ = &species.GetFittestOrganism();
	}
	return Trained::NeuralNetwork(champ->GetGenome());
}

auto NeuralNetworkTrainer::TrainGenerationAndLogUsingBodies(SpeciesManager::Bodies& bodies) -> void {
	species.Repopulate(bodies);
	species.LetGenerationLive();
	generationsPassed++;
	if (loggingEnabled) {
		logger.LogGeneration(generationsPassed, GetJSON());
		logger.LogMetadata(species.GetFittestOrganism().GetOrCalculateRawFitness());
	}
}

auto NeuralNetworkTrainer::GetJSON() const -> std::string {
	std::string s("{");
	s += "\"Parameters\";";
	s += GetParameters().GetJSON();
	s += "\"generationsPassed\":";
	s += std::to_string(generationsPassed);
	s += ",";
	s += "\"species\":[";
	for (const auto& sp : species) {
		s += sp.GetJSON();
		s += ",";
	}
	s.pop_back();
	s += "]}";
	return s;
}
