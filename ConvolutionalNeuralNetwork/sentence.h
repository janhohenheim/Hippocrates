#pragma once
#include "iinput_data.h"
#include <string>

namespace Convolutional {
namespace InputData {

class Sentence : public IInputData {
public:
	using Type = std::string;
	Sentence(Type sentence) :sentence(sentence){};
	auto GetMultiDimensionalMatrix() const->MultiMatrix override;

private:
	Type sentence;
};

}
}
