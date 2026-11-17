#include "matrix.hpp"
#include <cctype>
#include <istream>
#include <limits>
#include <stdexcept>

namespace merkulov {
  namespace detail {
    static void readSeparator(std::istream & input)
    {
      if (input.eof()) {
        return;
      }
      char separator = 0;
      if (!input.get(separator)) {
        if (input.bad() || !input.eof()) {
          throw std::runtime_error("Failed to read the matrix");
        }
      } else if (!std::isspace(static_cast< unsigned char >(separator))) {
        throw std::runtime_error("Expected whitespace between numbers");
      }
    }
  }
}

std::size_t merkulov::readDimension(std::istream & input)
{
  long long value = 0;
  if (!(input >> value) || (value < 0)) {
    throw std::runtime_error("Invalid matrix dimensions");
  }
  if (static_cast< unsigned long long >(value) > std::numeric_limits< std::size_t >::max()) {
    throw std::runtime_error("Matrix dimension is too large");
  }
  detail::readSeparator(input);
  return static_cast< std::size_t >(value);
}

void merkulov::readMatrix(std::istream & input, int * matrix, std::size_t size)
{
  for (std::size_t index = 0; index < size; ++index) {
    if (!(input >> matrix[index])) {
      throw std::runtime_error("Invalid matrix element");
    }
    detail::readSeparator(input);
  }
  char extra = 0;
  if (input >> extra) {
    throw std::runtime_error("Unexpected data after the matrix");
  }
  if (input.bad() || !input.eof()) {
    throw std::runtime_error("Failed to read the matrix");
  }
}

std::size_t merkulov::findLongestColumn(const int * matrix, std::size_t rows, std::size_t columns)
{
  if ((rows == 0) || (columns == 0)) {
    return 0;
  }
  std::size_t longest = 0;
  std::size_t result = 0;
  for (std::size_t column = 0; column < columns; ++column) {
    std::size_t length = 1;
    if (length > longest) {
      longest = length;
      result = column + 1;
    }
    for (std::size_t row = 1; row < rows; ++row) {
      if (matrix[row * columns + column] == matrix[(row - 1) * columns + column]) {
        ++length;
      } else {
        length = 1;
      }
      if (length > longest) {
        longest = length;
        result = column + 1;
      }
    }
  }
  return result;
}
