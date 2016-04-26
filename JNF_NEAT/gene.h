#pragma once
#include <cstddef>

struct Gene {
	public:
		Gene();
		Gene(const Gene& other) = default;
        Gene(Gene&& other) = default;
		~Gene() = default;
		
		Gene& operator=(const Gene& other) = default;

        std::size_t from = 0;
		std::size_t to = 0;
		float weight = 0.0f;
		std::size_t historicalMarking = numberOfExistingGenes;
		bool isEnabled = true;
		void SetRandomWeight();

	private:
		static std::size_t numberOfExistingGenes;
};