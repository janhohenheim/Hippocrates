#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ISpecimen&> & population) :
	population(population)
{
}

NeuralNetwork NeuralNetworkTrainer::Breed(const ISpecimen & mother, const ISpecimen & father) const
{
	std::vector<Gene> childGenes;
	if (mother.GetFitness() == father.GetFitness())
	{
		// TODO jnf
		// Do Stuff with the genes
	} else
	{
		// TODO jnf
		// Do Stuff with the genes
	}
	NeuralNetwork child(childGenes);

	// It may look inefective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}
