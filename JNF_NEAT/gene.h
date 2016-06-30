#pragma once
#include <cstddef>
#include <string>
namespace JNF_NEAT {

	struct Gene {
		public:
			Gene();
			Gene(const Gene& other) = default;
			Gene(Gene&& other) = default;
			~Gene() = default;
			Gene& operator=(const Gene& other) = default;
			Gene& operator=(Gene&& other) = default;

			std::size_t from = 0;
			std::size_t to = 0;
			float weight = 0.0f;
			std::size_t historicalMarking = numberOfExistingGenes++;
			bool isEnabled = true;
			bool isRecursive = false;
			void SetRandomWeight();
			std::string GetJSON() const;

		private:
			static std::size_t numberOfExistingGenes;
	};

}