#pragma once
#include "multi_matrix.hpp"
#include "interface.hpp"

namespace Convolutional::InputData {

class IInputData : public Hippocrates::Utility::Interface {
public:
	using Hippocrates::Utility::Interface::Interface;

	virtual auto GetMultiDimensionalMatrix() const -> MultiMatrix = 0;
};

}
