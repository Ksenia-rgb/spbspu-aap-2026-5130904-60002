#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <new>

namespace udovichenko
{
  constexpr int MAX_MATRIX_ELEMENTS_COUNT = 10000;

  bool readInputFileToMatrix(std::ifstream &input_file, int *matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(input_file >> matrix[i * cols + j]))
        {
          return false;
        }
      }
    }
    return true;
  }

  long long findMinSumSecondaryDiagonal(const int *matrix, int rows, int cols)
  {
    if (rows == 0 || cols == 0 || (rows == 1 && cols == 1))
    {
      return 0;
    }
    long long min_sum = std::numeric_limits< long long >::max();
    for (int col = 0; col < cols - 1; col++)
    {
      long long current_sum = 0;
      for (int i = 0, j = col; i < rows && j >= 0; i++, j--)
      {
        current_sum += matrix[i * cols + j];
      }
      min_sum = std::min(min_sum, current_sum);
    }
    for (int row = 1; row < rows; row++)
    {
      long long current_sum = 0;
      for (int i = row, j = cols - 1; i < rows && j >= 0; i++, j--)
      {
        current_sum += matrix[i * cols + j];
      }
      min_sum = std::min(min_sum, current_sum);
    }
    return min_sum;
  }
}

int main(int argc, const char *argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments" << '\n';
    return 1;
  }
  const char *const num = argv[1];
  std::ifstream input_file(argv[2]);
  if (!input_file)
  {
    std::cerr << "Cannot open input file" << '\n';
    return 1;
  }

  int rows = 0;
  int cols = 0;
  input_file >> rows >> cols;
  if (input_file.fail())
  {
    std::cerr << "Failed to read rows and cols for matrix" << '\n';
    return 2;
  }
  if (rows < 0 || cols < 0)
  {
    std::cerr << "Invalid values for rows and cols for matrix" << '\n';
    return 2;
  }

  bool read_matrix_elements = false;
  long long result = 0;

  if (std::strcmp(num, "1") == 0)
  {
    int matrix[udovichenko::MAX_MATRIX_ELEMENTS_COUNT] = {};
    read_matrix_elements = udovichenko::readInputFileToMatrix(input_file, matrix, rows, cols);
    if (read_matrix_elements)
    {
      result = udovichenko::findMinSumSecondaryDiagonal(matrix, rows, cols);
    }
  }
  else if (std::strcmp(num, "2") == 0)
  {
    int *matrix = nullptr;
    try
    {
      matrix = new int[rows * cols]{};
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Cannot allocate matrix" << '\n';
      return 1;
    }
    read_matrix_elements = udovichenko::readInputFileToMatrix(input_file, matrix, rows, cols);
    if (read_matrix_elements)
    {
      result = udovichenko::findMinSumSecondaryDiagonal(matrix, rows, cols);
    }
    delete[] matrix;
  }
  else
  {
    std::cerr << "First parameter is not a number or out of range" << '\n';
    return 1;
  }
  if (!read_matrix_elements)
  {
    std::cerr << "Failed to read matrix elements" << '\n';
    return 2;
  }

  std::ofstream output_file(argv[3]);
  if (!output_file)
  {
    std::cerr << "Cannot open output file" << '\n';
    return 1;
  }
  output_file << result << '\n';
  output_file.close();
  if (!output_file)
  {
    std::cerr << "Failed to write to output file" << '\n';
    return 1;
  }

  return 0;
}
