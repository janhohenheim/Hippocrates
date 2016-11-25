#include "InputData/image.hpp"

using namespace Convolutional;
using namespace Convolutional::InputData;

Convolutional::InputData::Image::Image(const char * filename)
{
}

auto Image::GetMultiDimensionalMatrix() const -> MultiMatrix {
	Matrix::Size imageSize{ 1920, 1080 };
	Matrix r{ imageSize };
	Matrix g{ imageSize };
	Matrix b{ imageSize };
	Matrix a{ imageSize };

	Matrix::element_t pixelVal = 10;
	r.ElementAt({ 100, 10 }) = pixelVal;

    return MultiMatrix({r,g,b,a});
}
