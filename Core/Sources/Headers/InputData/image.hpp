#pragma once

#include <Magick++.h>
#include "iinput_data.hpp"

namespace Convolutional::InputData {

class Image : public IInputData {
private:
	Magick::Image image;

public:
	using Type = std::nullptr_t;

	Image(const char* filename) throw(std::exception);
	auto GetMultiDimensionalMatrix() const -> MultiMatrix override;
};

}
