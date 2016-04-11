#include "gene_mutator.h"
#include "gene_examinator.h"
GeneMutator::GeneMutator(const TrainingParameters & parameters) :
	parameters(parameters)
{
}

void GeneMutator::MutateGenes(std::vector<Gene> & genes) const{
	if (ShouldAddConnection()) {
		AddRandomConnection(genes);
	}
	else
	if (ShouldAddNeuron()) {
		AddRandomNeuron(genes);
	}
	else {
		ShuffleWeights(genes);
	}
}

bool GeneMutator::DidChanceOccure(float chance)
{
	auto num = rand() % 100;
	return num < int(100.0f * chance);
}

void GeneMutator::AddRandomNeuron(std::vector<Gene>& genes) const
{
	Gene * randGene = nullptr;
	do {
		int num = rand() % genes.size();
		randGene = &genes[num];
	} while (!randGene->isEnabled);

	auto numberOfNeurons = GeneExaminator::GetNumberOfNeuronsInGenes(genes);

	Gene g1(*randGene);
	g1.to = numberOfNeurons;
	genes.push_back(std::move(g1));

	Gene g2(*randGene);
	g2.from = numberOfNeurons;
	genes.push_back(std::move(g2));

	randGene->isEnabled = false;
}

void GeneMutator::AddRandomConnection(std::vector<Gene>& genes) const
{
	auto GetRandomNumberBetween = [](unsigned min, unsigned max) {
		return rand() % (max - min) + min;
	};

	Gene newConnection;
	auto numberOfNeurons = GeneExaminator::GetNumberOfNeuronsInGenes(genes) - 1U;

	newConnection.from = GetRandomNumberBetween(0U, numberOfNeurons - 1U);
	newConnection.to = GetRandomNumberBetween(newConnection.from + 1, numberOfNeurons);

	genes.push_back(newConnection);
}

void GeneMutator::ShuffleWeights(std::vector<Gene>& genes) const
{
	for (auto & gene : genes) {
		if (ShouldMutateWeight()) {
			MutateWeightOfGene(gene);
		}
	}
}

void GeneMutator::MutateWeightOfGene(Gene & gene) const
{
	constexpr float chanceOfTotalWeightReset = 0.1f;
	if (DidChanceOccure(chanceOfTotalWeightReset)) {
		gene.SetRandomWeight();
	}
	else {
		PerturbWeight(gene.weight);
	}
}

void GeneMutator::PerturbWeight(float & weight) const
{
	constexpr float perturbanceBoundaries = 0.2f;
	auto perturbance = (float)(rand() % 10'000) / 10'000.0f * perturbanceBoundaries;
	if (rand() % 2) {
		perturbance = -perturbance;
	}
	weight *= perturbance;
}
