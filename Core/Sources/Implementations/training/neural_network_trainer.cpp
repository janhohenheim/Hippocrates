#include "training/neural_network_trainer.hpp"
#include <sstream>

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
		std::stringstream log;
		log << *this;
		logger.LogGeneration(generationsPassed, log);
		logger.LogMetadata(species.GetFittestOrganism().GetOrCalculateRawFitness());
	}
}

std::ostream & Hippocrates::Training::operator<<(std::ostream & stream, const NeuralNetworkTrainer & neuralNetworkTrainer)
{
	stream << "{" <<
	"\"Parameters\":" <<
	GetParameters() <<
	",\"generationsPassed\":" <<
	std::to_string(neuralNetworkTrainer.generationsPassed) <<
	"," <<
	"\"species\":[";
	auto& species = neuralNetworkTrainer.species;
	const auto speciesCount = species.GetSpeciesCount();
	for (std::size_t i = 0; i < speciesCount - 1; ++i) {
		stream << species[i] << ",";
	}
	stream << species[speciesCount - 1] << "]}";
	return stream;
}
