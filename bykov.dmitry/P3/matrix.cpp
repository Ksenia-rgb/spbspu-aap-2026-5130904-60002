#include "matrix.hpp"
#include <cctype>
#include <cstddef>
#include <istream>
#include <limits>
#include <ostream>

namespace bykov
{
  namespace
  {
    bool readInteger(std::istream& input, int& value)
    {
      if (!(input >> value))
      {
        return false;
      }
      if (input.eof())
      {
        return true;
      }
      const int next = input.peek();
      return !input.bad() && (input.eof() || std::isspace(next));
    }
  }
}

bool bykov::readSize(std::istream& input, std::size_t& rows, std::size_t& cols)
{
  int read_rows = 0;
  int read_cols = 0;
  if (!readInteger(input, read_rows) || !readInteger(input, read_cols) || read_rows < 0 || read_cols < 0)
  {
    return false;
  }
  rows = static_cast< std::size_t >(read_rows);
  cols = static_cast< std::size_t >(read_cols);
  return rows == 0 || cols <= std::numeric_limits< std::size_t >::max() / rows;
}

bool bykov::readMatrix(std::istream& input, int* matrix, std::size_t count)
{
  for (std::size_t i = 0; i < count; ++i)
  {
    if (!readInteger(input, matrix[i]))
    {
      return false;
    }
  }
  if (!input.eof())
  {
    input >> std::ws;
  }
  return input.eof() && !input.bad();
}

void bykov::writeMatrix(std::ostream& output, const int* matrix, std::size_t rows, std::size_t cols)
{
  output << rows << " " << cols;
  for (std::size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << matrix[i];
  }
}
