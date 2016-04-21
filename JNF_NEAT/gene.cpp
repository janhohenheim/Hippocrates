#include "gene.h"
#include <iostream>

size_t Gene::numberOfExistingGenes = 0U;

Gene::Gene()
{
	SetRandomWeight();
	numberOfExistingGenes++;
	std::cout << "New Gene created with historical marking: " << historicalMarking << "\t Number of total Genes: " << numberOfExistingGenes << std::endl;
}

void Gene::SetRandomWeight()
{
	weight = (float)(rand() % 10'000) / 10'000.0f;
}
