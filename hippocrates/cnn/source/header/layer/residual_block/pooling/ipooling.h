#pragma once
#include "layer/residual_block/iresidual_block.hpp"

namespace Convolutional::Layer::ResidualBlock::Pooling {

class IPooling : public IResidualBlock {
public:
	using IResidualBlock::IResidualBlock;
};

}
