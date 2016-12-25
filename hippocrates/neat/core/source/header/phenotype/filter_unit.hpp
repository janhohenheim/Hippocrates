#pragma once
#include "phenotype/network_components/transformation_unit.hpp"
#include "cnn/source/header/layer/filter.hpp"

using namespace Hippocrates;
using namespace Phenotype;
using namespace Convolutional::Layer;

namespace Hippocrates::Phenotype::NetworkComponents::Convolutional {

class FilterUnit : ITransformationUnit {
	
public:
	Filter filter;

};

}
