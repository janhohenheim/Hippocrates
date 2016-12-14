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

std::ostream & Hippocrates::Training::operator«(std::ostream & stream, const NeuralNetworkTrainer & neuralNetworkTrainer)
{
	stream << "{" <<
	"\"Parameters\":" <<
	GetParameters() <<
	",\"generationsPassed\":" <<
	std::to_string(neuralNetworkTrainer.generationsPassed) <<
	"," <<
	"\"species\":[";
	for (const auto& sp : neuralNetworkTrainer.species) {
		stream << sp <<
		",";
	}
	stream << pop_back() <<
	"]}";
	return stream;
}
