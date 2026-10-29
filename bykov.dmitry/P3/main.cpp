#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <new>
#include "matrix.hpp"

namespace bykov
{
  namespace
  {
    const int arguments_count = 4;
    const int input_argument = 2;
    const int output_argument = 3;
    const char* const static_mode = "1";
    const char* const dynamic_mode = "2";
    const std::size_t max_static_size = 10000;
    const int argument_error = 1;
    const int data_error = 2;

    int processMatrix(std::istream& input, const char* output_name, int* matrix, std::size_t rows, std::size_t cols)
    {
      if (bykov::readMatrix(input, matrix, rows * cols) != rows * cols)
      {
        std::cerr << "Error: the file does not contain a matrix\n";
        return data_error;
      }
      bykov::addLayerNumbers(matrix, rows, cols);
      std::ofstream output(output_name);
      if (!output)
      {
        std::cerr << "Error: cannot open the output file\n";
        return data_error;
      }
      bykov::writeMatrix(output, matrix, rows, cols);
      output << "\n";
      return 0;
    }
  }
}

int main(int argc, char** argv)
{
  if (argc != bykov::arguments_count)
  {
    std::cerr << "Error: expected arguments: num input output\n";
    return bykov::argument_error;
  }
  const bool is_static = std::strcmp(argv[1], bykov::static_mode) == 0;
  const bool is_dynamic = std::strcmp(argv[1], bykov::dynamic_mode) == 0;
  if (!is_static && !is_dynamic)
  {
    std::cerr << "Error: the first argument must be 1 or 2\n";
    return bykov::argument_error;
  }
  std::ifstream input(argv[bykov::input_argument]);
  if (!input)
  {
    std::cerr << "Error: cannot open the input file\n";
    return bykov::data_error;
  }
  std::size_t rows = 0;
  std::size_t cols = 0;
  if (!bykov::readSize(input, rows, cols))
  {
    std::cerr << "Error: the file does not contain a matrix\n";
    return bykov::data_error;
  }
  if (is_static)
  {
    if (rows * cols > bykov::max_static_size)
    {
      std::cerr << "Error: the matrix is too big for a fixed array\n";
      return bykov::data_error;
    }
    int matrix[bykov::max_static_size] = {};
    return bykov::processMatrix(input, argv[bykov::output_argument], matrix, rows, cols);
  }
  int* matrix = nullptr;
  try
  {
    matrix = new int[rows * cols];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: not enough memory\n";
    return bykov::data_error;
  }
  const int result = bykov::processMatrix(input, argv[bykov::output_argument], matrix, rows, cols);
  delete[] matrix;
  return result;
}
