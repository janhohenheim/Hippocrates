#pragma once
#include "transformation_unit.hpp"
#include "cnn/source/header/layer/pooler/ipooler.hpp"

using namespace Hippocrates;
using namespace Phenotype;
using namespace Convolutional::Layer;

namespace Hippocrates::Phenotype::NetworkComponents::Convolutional {

class PoolerUnit : ITransformationUnit {

public:
	Pooler::IPooler pooler;

	explicit PoolerUnit(Pooler::IPooler&& filter) : pooler(std::move(filter)) { }
};

}
