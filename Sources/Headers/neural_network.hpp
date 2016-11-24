#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "multi_matrix.hpp"
#include "layers.hpp"
#include "multi_matrix_factory.hpp"
#include "filter.hpp"

namespace Convolutional {

	template <typename Classification>
	class NeuralNetwork {
	public:
		explicit NeuralNetwork(Layer::Layers layers) : layers{ std::move(layers) } {	}

		auto ClassifyMultiMatrix(const InputData::IInputData& input) {
			return ClassifyMultiMatrix(MultiMatrixFactory::GetMultiMatrix(input));
		}

		auto ClassifyMultiMatrix(const MultiMatrix& multiMatrix) {
			auto outputs = GetOutputsUsingMatrix(multiMatrix);
			auto maxOutput = std::max_element(outputs.begin(), outputs.end());
			auto outputIndex = std::distance(outputs.begin(), maxOutput);
			return static_cast<Classification>(outputIndex);
		}

		auto GetOutputsUsingMatrix(const MultiMatrix& multiMatrix) {
			auto processedMultiMatrix{ multiMatrix };
			for (const auto& layer : layers) {
				processedMultiMatrix = layer->ProcessMultiMatrix(processedMultiMatrix);
			}
			if (processedMultiMatrix.GetElementCount() != 1)
				throw std::logic_error("The last layer did not make the MultiMatrix two dimensional");

			std::vector<Matrix::elementType> outputs;
			outputs.reserve(processedMultiMatrix.GetDimensionCount());
			for (const auto& matrix : processedMultiMatrix) {
				outputs.push_back(matrix.GetElementAt({0,0 }));
			}
			return outputs;
		}

	private:
		Layer::Layers layers;
	};

}