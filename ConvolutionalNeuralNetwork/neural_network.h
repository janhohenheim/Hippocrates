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
    auto ApplyToAllMatrices(T&& function) -> void {
        MultiDimensionalMatrix::SubDimensionType featureDimensions;
        featureDimensions.reserve(matrix.GetDimensionCount());
        for (auto& submatrix : matrix) {
            for (std::size_t y = 0; y < submatrix.GetSize().height; ++y) {
                for (std::size_t x = 0; x < submatrix.GetSize().width; ++x) {
                    Matrix::Position pos;
                    pos.x = x;
                    pos.y = y;
                    auto processedMatrix = function(pos, submatrix);
                    featureDimensions.push_back(std::move(processedMatrix));
                }
            }
        }
        MultiDimensionalMatrix feature(std::move(featureDimensions));
    }

private:
	MultiDimensionalMatrix matrix;
};

}
