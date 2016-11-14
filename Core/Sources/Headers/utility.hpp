#ifdef _WIN32
	#define HIPPOCRATES_SSCANF sscanf_s
#else
	#define HIPPOCRATES_SSCANF sscanf
#endif

#pragma once
#include <random>
#include <algorithm>

namespace Hippocrates {

class Utility {

public:
template <typename T>
static auto GetRandomNumberBetween(T min, T max)
{
	std::uniform_int_distribution<T> distribution(min, max);
	return distribution(engine);
}

static inline auto FlipACoin() {
	// The currency of the coin is determined by the OS
	return GetRandomNumberBetween(0, 1) == 0;
}

template <typename T>
static inline auto DidChanceOccure(T chance) {
	auto randnum = GetRandomNumberBetween(static_cast<T>(0.0), static_cast<T>(1.0));
	return randnum < chance;
}

template <typename It>
static auto GetRandomElement(It begin, It end) {
	auto dist = std::distance(begin, end);
	if (dist != 0) {
		auto rnd = GetRandomNumberBetween(0, static_cast<int>(dist) - 1);
		std::advance(begin, rnd);
	}
	return begin;
}

template <typename T>
static auto GetRandomElement(T&& container){
	return GetRandomElement(container.begin(), container.end());
}


template<typename T>
static auto Shuffle(T&& container) {
	return std::shuffle(container.begin(), container.end(),	engine);
}


private:
	static std::random_device randomDevice;
	static std::mt19937 engine;
};


template <>
inline auto Utility::GetRandomNumberBetween(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(engine);
}

template <>
inline auto Utility::GetRandomNumberBetween(double min, double max)
{
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(engine);
}

}
