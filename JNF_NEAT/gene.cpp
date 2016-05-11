#include "gene.h"
#include <stdlib.h>

size_t Gene::numberOfExistingGenes = 0U;

Gene::Gene()
{
	SetRandomWeight();
	numberOfExistingGenes++;
}

void Gene::SetRandomWeight()
{
	weight = (float)(rand() % 10'000) / 9'999.0f;
    if (rand() % 2) {
        weight = -weight;
    }
}