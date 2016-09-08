#pragma once
#include <memory>
#include <functional>
#include "multi_dimensional_matrix.h"
#include "ipooler.h"
#include "neuron.h"
#include "multi_matrix_factory.h"
#include "iinput_data.h"

namespace Convolutional {

class NeuralNetwork {
public:
	NeuralNetwork(MultiDimensionalMatrix matrix);
	NeuralNetwork(const InputData::IInputData& input) : 
		NeuralNetwork(std::move(MultiMatrixFactory::GetMultiMatrix(input))) {}

	auto Pool(const IPooler& pooler) -> void;
	auto Subsample(const Neuron& neuron) -> void;

    template<typename T>
    auto ApplyToAllDimensions(T&& function) {
        MultiDimensionalMatrix::SubDimensionType dimensions;
        dimensions.reserve(matrix.GetDimensionCount());
        for (auto& submatrix : matrix) {
            Matrix::Position pos;
            for (; pos.y < submatrix.GetSize().height; ++pos.y) {
                for (; pos.x < submatrix.GetSize().width; ++pos.x) {
                    auto processedMatrix = function(pos, submatrix);
                    dimensions.push_back(std::move(processedMatrix));
                }
            }
        }
        return dimensions;
    }

private:
	MultiDimensionalMatrix matrix;
};

}
