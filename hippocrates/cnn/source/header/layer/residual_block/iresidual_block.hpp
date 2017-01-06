#pragma once
#include "layer/ilayer.hpp"
#include "layer/convolution.hpp"

namespace Convolutional::Layer::ResidualBlock {

class IResidualBlock : public ILayer {
public:
	using ILayer::ILayer;
};

}
