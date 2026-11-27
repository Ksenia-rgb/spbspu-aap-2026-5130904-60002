#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include "matrix.hpp"

int main(int argc, char * argv[])
{
  const int argument_count = 4;
  if (argc != argument_count) {
    std::cerr << "Usage: lab 1|2 input output\n";
    return 1;
  }
  const bool use_fixed_array = std::strcmp(argv[1], "1") == 0;
  if (!use_fixed_array && (std::strcmp(argv[1], "2") != 0)) {
    std::cerr << "Storage mode must be 1 or 2\n";
    return 1;
  }
  try {
    std::ifstream input(argv[2]);
    if (!input) {
      throw std::runtime_error("Cannot open the input file");
    }
    const std::size_t rows = merkulov::readDimension(input);
    const std::size_t columns = merkulov::readDimension(input);
    const std::size_t max_elements = std::numeric_limits< std::size_t >::max() / sizeof(int);
    if ((columns != 0) && (rows > max_elements / columns)) {
      throw std::runtime_error("Matrix is too large");
    }
    const std::size_t size = rows * columns;
    std::size_t result = 0;
    if (use_fixed_array) {
      const std::size_t capacity = 10000;
      if (size > capacity) {
        throw std::runtime_error("Matrix exceeds the fixed array capacity");
      }
      int matrix[capacity] = {};
      merkulov::readMatrix(input, matrix, size);
      result = merkulov::findLongestColumn(matrix, rows, columns);
    } else {
      const std::unique_ptr< int[] > matrix(new int[size]);
      merkulov::readMatrix(input, matrix.get(), size);
      result = merkulov::findLongestColumn(matrix.get(), rows, columns);
    }
    input.close();
    std::ofstream output(argv[3]);
    if (!output) {
      throw std::runtime_error("Cannot open the output file");
    }
    output << result << '\n';
    output.close();
    if (!output) {
      throw std::runtime_error("Failed to write the result");
    }
  } catch (const std::exception & error) {
    std::cerr << error.what() << '\n';
    return 2;
  }
  return 0;
}
