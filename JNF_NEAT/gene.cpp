#include "gene.h"

unsigned int Gene::numberOfExistingGenes = 0U;

Gene::Gene()
{
	SetRandomWeight();
	numberOfExistingGenes++;
}

void Gene::SetRandomWeight()
{
	weight = (float)(rand() % 10'000) / 10'000.0f;
}
