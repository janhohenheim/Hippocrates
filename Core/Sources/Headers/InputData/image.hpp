#pragma once
#include "iinput_data.hpp"

namespace Convolutional::InputData {

class Image : public IInputData {
public:
	using Type = std::nullptr_t;

	Image(const char* filename);
	auto GetMultiDimensionalMatrix() const -> MultiMatrix override;
};

}
