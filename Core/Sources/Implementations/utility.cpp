#include "../Headers/utility.hpp"
std::random_device Hippocrates::Utility::randomDevice;
std::mt19937 Hippocrates::Utility::engine(Hippocrates::Utility::randomDevice());