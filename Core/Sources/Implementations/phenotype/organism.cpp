#include <cstdlib>
#include <algorithm>

#include "phenotype/organism.hpp"
#include "utility/random.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Phenotype;

Organism::Organism(Body::IBody& body, NeuralNetwork&& network) :
	body(&body),
	network(std::move(network))
{
}

auto Organism::Update() -> void {
	if (!body->HasFinishedTask()) {
		const auto inputs(body->ProvideNetworkWithInputs());
		const auto outputs(network.GetOutputsUsingInputs(inputs));
		body->Update(outputs);
		isFitnessUpToDate = false;
	}
}

auto Organism::GetOrCalculateFitness() const -> Type::fitness_t {
	return GetOrCalculateRawFitness() * fitnessModifier;
}

auto Organism::GetOrCalculateRawFitness() const -> Type::fitness_t {
	if (!isFitnessUpToDate) {
		fitness = body->GetFitness();
		isFitnessUpToDate = true;
	}
	return fitness;
}

auto Organism::BreedWith(const Organism& partner, Training::InnovationCacher& currGenerationInnovations) const -> NeuralNetwork {
	auto parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
	const Organism* dominantParent = nullptr;
	if (parentsHaveSameFitness) {
		dominantParent = Utility::Random::FlipACoin() ? this : &partner;
	}
	else {
		dominantParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
	}
	// TODO jnf: conform to the paper
	auto childGenome(dominantParent->GetGenome());

	const auto sizeOfSmallerParent = std::min(this->GetGenome().GetGeneCount(), partner.GetGenome().GetGeneCount());
	auto& partnerGenome = partner.GetGenome();
	auto AreSameAt = [&](std::size_t i) {
		return childGenome[i] == partnerGenome[i];
	};
	for (std::size_t i = 0U; i < sizeOfSmallerParent && AreSameAt(i); ++i) {
		if (Utility::Random::FlipACoin()) {
			childGenome[i].weight = partnerGenome[i].weight;
		}
	}
	NeuralNetwork child(std::move(childGenome), currGenerationInnovations);
	return child;
}

std::ostream & Hippocrates::Phenotype::operator<<(std::ostream & stream, const Organism & organism)
{
	stream << "{\"fitness\":" <<
	std::to_string(organism.GetOrCalculateRawFitness()) <<
	"," <<
	"\"fitnessModifier\":" <<
	std::to_string(organism.fitnessModifier) <<
	"," <<
	"\"network\":" <<
	organism.network <<
	"}";
	return stream;
}
