#pragma once
#include "iinput_data.h"

namespace Convolutional {
namespace InputData {

class Image : public IInputData {
public:
	using Type = nullptr_t;
    auto GetMultiDimensionalMatrix() const->MultiDimensionalMatrix override;
};

}
}
