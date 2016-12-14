#include "backpropagation.hpp"

using namespace Convolutional::Learning;

auto Backpropagation::IsFinished() -> bool {
static int runs = 2;
return !runs--;
}