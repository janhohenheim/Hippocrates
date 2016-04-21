#pragma once
#include "gene.h"
#include <vector> 

class GeneExaminator {
	public:
		static size_t GetNumberOfNeuronsInGenes(const std::vector<Gene>& genes);
};