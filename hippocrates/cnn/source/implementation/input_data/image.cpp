#include "input_data/image.hpp"
#include <iostream>

using namespace Convolutional;
using namespace Convolutional::InputData;

Image::Image(const char * filename) :
	image("32x32", "white")
	//image(filename)
{
}

auto Image::GetMultiDimensionalMatrix() const -> MultiMatrix {
	const auto w = image.columns();
	const auto h = image.rows();

	Matrix::Size imageSize{ w, h };
	Matrix r{ imageSize };
	Matrix g{ imageSize };
	Matrix b{ imageSize };
	Matrix a{ imageSize };

	auto *pixels = const_cast<Magick::Image*>(&image)->getPixels(0, 0, w, h);

	for(std::size_t i = 0; i < w; i++) {
		for(std::size_t j = 0; j < h; j++) {
			r.ElementAt({j, i}) = pixels[j * w + i].red;
			g.ElementAt({j, i}) = pixels[j * w + i].green;
			b.ElementAt({j, i}) = pixels[j * w + i].blue;
			if (image.matte())
				a.ElementAt({j, i}) = pixels[j * w + i].opacity;
		}
	}

	return image.matte() ? MultiMatrix({r,g,b,a}) : MultiMatrix({r,g,b});
}
