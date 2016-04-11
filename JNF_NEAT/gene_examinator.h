#pragma once
#include "gene.h"
#include <vector> 

class GeneExaminator {
	public:
		static unsigned int GetNumberOfNeuronsInGenes(const std::vector<Gene>& genes);
};