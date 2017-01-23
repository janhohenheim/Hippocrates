#include "random.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Utility;

std::random_device Random::randomDevice;
std::mt19937 Random::engine(Random::randomDevice());
