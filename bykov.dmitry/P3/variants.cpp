#include "variants.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace bykov
{
  namespace
  {
    std::size_t getMin(std::size_t first, std::size_t second)
    {
      return first < second ? first : second;
    }
  }
}

void bykov::addLayerNumbers(int* matrix, std::size_t rows, std::size_t cols)
{
  if (cols == 0)
  {
    return;
  }
  const int maximum = std::numeric_limits< int >::max();
  for (std::size_t i = 0; i < rows; ++i)
  {
    for (std::size_t j = 0; j < cols; ++j)
    {
      const std::size_t layer = getMin(getMin(i, j), getMin(rows - 1 - i, cols - 1 - j));
      if (layer >= static_cast< std::size_t >(maximum))
      {
        throw std::overflow_error("The layer number is too large");
      }
      const int increment = static_cast< int >(layer) + 1;
      if (matrix[i * cols + j] > maximum - increment)
      {
        throw std::overflow_error("The transformed matrix element overflows");
      }
    }
  }
  for (std::size_t i = 0; i < rows; ++i)
  {
    for (std::size_t j = 0; j < cols; ++j)
    {
      const std::size_t layer = getMin(getMin(i, j), getMin(rows - 1 - i, cols - 1 - j));
      matrix[i * cols + j] += static_cast< int >(layer) + 1;
    }
  }
}
