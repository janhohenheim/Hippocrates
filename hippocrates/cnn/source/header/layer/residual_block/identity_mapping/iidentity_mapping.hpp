#pragma once
#include "layer/residual_block/iresidual_block.hpp"

namespace Convolutional::Layer::ResidualBlock::IdentityMapping {

class IIdentityMapping : public IResidualBlock {
public:
	using IResidualBlock::IResidualBlock;
};

}
