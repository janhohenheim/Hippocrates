#pragma once
#include "iinput_data.hpp"

namespace Convolutional::InputData {

class Image : public IInputData {
public:
	using Type = std::nullptr_t;
	auto GetMultiDimensionalMatrix() const -> MultiMatrix override;
};

}
