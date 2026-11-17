#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iosfwd>

namespace merkulov {
  std::size_t readDimension(std::istream & input);
  void readMatrix(std::istream & input, int * matrix, std::size_t size);
  std::size_t findLongestColumn(const int * matrix, std::size_t rows, std::size_t columns);
}

#endif
