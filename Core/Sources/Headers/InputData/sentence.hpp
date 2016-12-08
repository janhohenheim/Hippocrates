#pragma once
#include "iinput_data.hpp"
#include <string>

namespace Convolutional::InputData {

class Sentence : public IInputData {
public:
	using Type = std::string;
	using IInputData::IInputData;

	Sentence(Type sentence) :sentence(sentence){};
	Sentence(const Sentence&) = default;
	Sentence(Sentence&&) = default;

	auto GetMultiDimensionalMatrix() const->MultiMatrix override;

private:
	Type sentence;
};

}
