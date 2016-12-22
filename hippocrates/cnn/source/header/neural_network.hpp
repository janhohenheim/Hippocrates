#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "multi_matrix.hpp"
#include "multi_matrix_factory.hpp"
#include "layer/layers.hpp"
#include "layer/filter.hpp"

namespace Convolutional {

	template <typename Classification>
	class NeuralNetwork {
	public:
		explicit NeuralNetwork(Layer::Layers layers) : layers{ std::move(layers) } {	}
		NeuralNetwork(const NeuralNetwork&) = default;
		NeuralNetwork(NeuralNetwork&&) = default;

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

			std::vector<Matrix::element_t> outputs;
			outputs.reserve(processedMultiMatrix.GetDimensionCount() * processedMultiMatrix.GetElementCount());
			for (const auto& matrix : processedMultiMatrix)
				for (const auto element : matrix)
					outputs.push_back(element);
			return outputs;
		}

		Layer::Layers layers;
	};

}
