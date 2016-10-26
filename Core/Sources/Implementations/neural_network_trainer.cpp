#include "../Headers/neural_network_trainer.hpp"

using namespace Hippocrates;
using namespace std;

NeuralNetworkTrainer::NeuralNetworkTrainer(TrainingParameters parameters) :
	parameters(move(parameters)),
	species{ this->parameters }
{
}

auto NeuralNetworkTrainer::TrainUnsupervised(SpeciesManager::Bodies& bodies) -> TrainedNeuralNetwork {
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
	return TrainedNeuralNetwork(champ->GetGenome());
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

auto NeuralNetworkTrainer::GetJSON() const -> string {
	string s("{");
	s += "\"generationsPassed\":";
	s += to_string(generationsPassed);
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
