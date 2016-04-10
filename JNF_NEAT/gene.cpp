#include "gene.h"

unsigned int Gene::numberOfExistingGenes = 0U;

Gene::Gene()
{
	numberOfExistingGenes++;
}