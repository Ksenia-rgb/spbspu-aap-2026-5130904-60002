#include "matrix.hpp"
#include <cstddef>
#include <istream>
#include <ostream>

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

bool bykov::readSize(std::istream& input, std::size_t& rows, std::size_t& cols)
{
  int read_rows = 0;
  int read_cols = 0;
  input >> read_rows >> read_cols;
  if (!input || read_rows < 0 || read_cols < 0)
  {
    return false;
  }
  rows = static_cast< std::size_t >(read_rows);
  cols = static_cast< std::size_t >(read_cols);
  return true;
}

std::size_t bykov::readMatrix(std::istream& input, int* matrix, std::size_t count)
{
  std::size_t read = 0;
  while (read < count && (input >> matrix[read]))
  {
    ++read;
  }
  return read;
}

void bykov::writeMatrix(std::ostream& output, const int* matrix, std::size_t rows, std::size_t cols)
{
  output << rows << " " << cols;
  for (std::size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << matrix[i];
  }
}

void bykov::addLayerNumbers(int* matrix, std::size_t rows, std::size_t cols)
{
  for (std::size_t i = 0; i < rows; ++i)
  {
    for (std::size_t j = 0; j < cols; ++j)
    {
      const std::size_t layer = getMin(getMin(i, j), getMin(rows - 1 - i, cols - 1 - j));
      matrix[i * cols + j] += static_cast< int >(layer) + 1;
    }
  }
}
