#pragma once
#include "phenotype/network_components/transformation_unit.hpp"
#include "cnn/source/header/layer/relu.hpp"

using namespace Hippocrates;
using namespace Phenotype;
using namespace Convolutional::Layer;

namespace Hippocrates::Phenotype::NetworkComponents::Convolutional {

class ReluUnit : ITransformationUnit {

public:
	ReLU relu;

	explicit ReluUnit(ReLU&& filter) : relu(std::move(filter)) { }
};

}
