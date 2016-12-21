#pragma once

#include <Magick++.h>
#include "iinput_data.hpp"

namespace Convolutional::InputData {

class Image : public IInputData {
private:
	Magick::Image image;

public:
	using Type = std::nullptr_t;
	using IInputData::IInputData;

	Image(const char* filename); 
	Image(const Image&) = default;
	Image(Image&&) = default;

	auto GetMultiDimensionalMatrix() const -> MultiMatrix override;
};

}
