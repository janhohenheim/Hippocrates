#include "multi_matrix_factory.h"
#include "image.h"
#include "sentence.h"
using namespace Convolutional;


auto Convolutional::MultiMatrixFactory::GetMultiMatrix(const InputData::IInputData& input) -> MultiMatrix {
	if (const auto* image = dynamic_cast<const InputData::Image*>(&input)) {
		return image->GetMultiDimensionalMatrix();
	}
	if (const auto* sentence = dynamic_cast<const InputData::Sentence*>(&input)) {
		return sentence->GetMultiDimensionalMatrix();
	}

	throw std::invalid_argument("Input type provided is not supported");
}
