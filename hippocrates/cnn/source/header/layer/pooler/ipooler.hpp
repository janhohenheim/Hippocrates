#pragma once
#include "matrix.hpp"
#include "layer/ilayer.hpp"

namespace Convolutional::Layer::Pooler {

class IPooler : public ILayer {
public:
	using ILayer::ILayer;
};

}
