#include <algorithm>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(const NeuralNetworkTrainer::TrainingParameters & parameters) :
	parameters(parameters)
{
}

NeuralNetworkTrainer::NeuralNetworkTrainer(TrainingParameters && parameters) :
    parameters(parameters)
{
}

NeuralNetwork NeuralNetworkTrainer::Breed(ITrainable * mother, ITrainable * father)
{
	std::vector<Gene> childGenes;

	if (mother->GetOrCalculateFitness() == father->GetOrCalculateFitness()) {
		// TODO jnf
		// Do Stuff with the genes
	} else {
		// TODO jnf
		// Do Stuff with the genes
	}

    MaybeMutateGenes(childGenes);

	NeuralNetwork child(std::move(childGenes));
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
    this->population.clear();
    for (auto & i : population) {
        NeuralNetwork net = NeuralNetwork(parameters.numberOfInputs, parameters.numberOfOutputs);
        Individuum individuum(i, net);
        this->population.push_back(individuum);
    }
}

void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	do {
		Repopulate();
		LetGenerationLive();
	} while (GetFittestSpecimen().trainable->GetOrCalculateFitness() < fitnessToReach);
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	for(auto generation = 0U; generation < generationsToTrain; generation++){
		Repopulate();
		LetGenerationLive();
	}
}

NeuralNetworkTrainer::Individuum NeuralNetworkTrainer::GetFittestSpecimen() {
	// TODO jnf
	// Implementation
	return population.front();
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (auto & specimen : population){
		specimen.trainable->Update();
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf
	// Implementation
}

void NeuralNetworkTrainer::MaybeMutateGenes(std::vector<Gene> & genes)
{
    if (ShouldMutateWeights()) {
        MutateWeights(genes);
    }
    if (ShouldAddConnection()) {
        AddRandomConnection(genes);
    }
    if (ShouldAddNeuron()) {
        AddRandomNeuron(genes);
    }
}

unsigned int NeuralNetworkTrainer::GetNumberOfNeuronsInGenes(const std::vector<Gene>& genes)
{
    auto CompareToNeuron = [](const Gene& lhs, const Gene& rhs) {
        return lhs.to < rhs.to;
    };
    auto maxNeuronGene = std::max_element(genes.begin(), genes.end(), CompareToNeuron);
    return maxNeuronGene->to + 1U;
}

bool NeuralNetworkTrainer::DidChanceOccure(float chance)
{
    auto num = rand() % 100;
    return num < int(100.0f * chance);
}

void NeuralNetworkTrainer::MutateWeights(std::vector<Gene>& genes)
{
    // TODO jnf
    // Implementation
}

void NeuralNetworkTrainer::AddRandomNeuron(std::vector<Gene>& genes)
{
    Gene * randGene = nullptr;
    do {
        int num = rand() % genes.size();
        randGene = &genes[num];
    } while (!randGene->isEnabled);
    
    auto numberOfNeurons = GetNumberOfNeuronsInGenes(genes);
    
    Gene g1(*randGene);
    g1.to = numberOfNeurons;
    genes.push_back(std::move(g1));

    Gene g2(*randGene);
    g2.from = numberOfNeurons;
    genes.push_back(std::move(g2));

    randGene->isEnabled = false;
}

void NeuralNetworkTrainer::AddRandomConnection(std::vector<Gene>& genes)
{
    auto GetRandomNumberBetween = [](unsigned min, unsigned max) {
        return rand() % (max - min) + min;
    };

    Gene newConnection;
    auto numberOfNeurons = GetNumberOfNeuronsInGenes(genes) - 1U;

    newConnection.from = GetRandomNumberBetween(0U, numberOfNeurons - 1U);
    newConnection.to = GetRandomNumberBetween(newConnection.from + 1, numberOfNeurons);

    genes.push_back(newConnection);
}