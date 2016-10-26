#include "multi_matrix.hpp"

using namespace Convolutional;

MultiMatrix::MultiMatrix(SubDimensionType subDimensions) :
subDimensions(std::move(subDimensions))
{
}
