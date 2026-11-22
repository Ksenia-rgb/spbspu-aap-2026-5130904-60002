#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <iosfwd>

namespace bykov
{
  bool readSize(std::istream& input, std::size_t& rows, std::size_t& cols);
  std::size_t readMatrix(std::istream& input, int* matrix, std::size_t count);
  void writeMatrix(std::ostream& output, const int* matrix, std::size_t rows, std::size_t cols);
  void addLayerNumbers(int* matrix, std::size_t rows, std::size_t cols);
}

#endif
