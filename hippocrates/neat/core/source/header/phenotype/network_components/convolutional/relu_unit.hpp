#pragma once
#include "phenotype/network_components/transformation_unit.hpp"
#include "layer/relu.hpp"

using namespace Hippocrates;
using namespace Phenotype;
using namespace Convolutional::Layer;

namespace Hippocrates::Phenotype::NetworkComponents::Convolutional {

class ReluUnit : ITransformationUnit<ReLU> {
};

}
