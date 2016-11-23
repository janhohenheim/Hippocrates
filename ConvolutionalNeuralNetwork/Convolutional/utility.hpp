#pragma once
#include <random>

namespace Convolutional::Utility {
template <typename T>
auto GetRandomNumberBetween(T min, T max)
{
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());

    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(engine);
}

template <>
inline auto GetRandomNumberBetween(float min, float max) {
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());

    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

template <>
inline auto GetRandomNumberBetween(double min, double max) {
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());

    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(engine);
}


inline auto FlipACoin() {
    // The currency of the coin is determined by the OS
    return GetRandomNumberBetween(0, 1) == 0;
}

inline auto DidChanceOccure(float chance) {
    auto randnum = GetRandomNumberBetween(0.0f, 1.0f);
    return randnum < chance;
}

template <typename It>
auto GetRandomElement(It begin, It end) {
    auto dist = std::distance(begin, end);
    auto rnd = GetRandomNumberBetween(0, static_cast<int>(dist) - 1);
    std::advance(begin, rnd);
    return begin;
}

template <typename T>
auto GetRandomElement(T&& container){
    return GetRandomElement(container.begin(), container.end());
}

}
