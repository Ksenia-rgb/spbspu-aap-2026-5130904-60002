#include <iostream>
#include <fstream>
#include <string>
#include <new>
namespace gorkova
{
  const int max_size = 10000;
  const char* const stack_mode = "1";
  const char* const heap_mode = "2";
  const int argument_error = 1;
  const int data_error = 2;
  const int arguments_count = 4;
  bool readSizes(std::ifstream& in, int& rows, int& cols)
  {
    if (!(in >> rows >> cols))
    {
      return false;
    }
    if ((rows < 0) || (cols < 0))
    {
      return false;
    }
    if ((rows * cols) > max_size)
    {
      return false;
    }
    return true;
  }
  bool readToStack(std::ifstream& in, int matrix[max_size], int rows, int cols)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(in >> matrix[i * cols + j]))
        {
          return false;
        }
      }
    }
    return true;
  }
  int countColumnsStack(const int matrix[max_size], int rows, int cols)
  {
    int count = 0;
    for (int j = 0; j < cols; ++j)
    {
      bool has_duplicate = false;
      for (int i = 1; i < rows; ++i)
      {
        const int curr = matrix[i * cols + j];
        const int prev = matrix[(i - 1) * cols + j];
        if (curr == prev)
        {
          has_duplicate = true;
          break;
        }
      }
      if (!has_duplicate)
      {
        ++count;
      }
    }
    return count;
  }
  int** allocateMatrix(int rows, int cols)
  {
    int** const m = new int*[rows]();
    try
    {
      for (int i = 0; i < rows; ++i)
      {
        m[i] = new int[cols]();
      }
    }
    catch (...)
    {
      for (int i = 0; i < rows; ++i)
      {
        delete[] m[i];
      }
      delete[] m;
      throw;
    }
    return m;
  }
  void freeMatrix(int** m, int rows)
  {
    if (m == nullptr)
    {
      return;
    }
    for (int i = 0; i < rows; ++i)
    {
      delete[] m[i];
    }
    delete[] m;
  }
  bool readToDyn(std::ifstream& in, int** matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(in >> matrix[i][j]))
        {
          return false;
        }
      }
    }
    return true;
  }
  int countColumnsDyn(const int* const* matrix, int rows, int cols)
  {
    int count = 0;
    for (int j = 0; j < cols; ++j)
    {
      bool has_duplicate = false;
      for (int i = 1; i < rows; ++i)
      {
        if (matrix[i][j] == matrix[i - 1][j])
        {
          has_duplicate = true;
          break;
        }
      }
      if (!has_duplicate)
      {
        ++count;
      }
    }
    return count;
  }
}
int main(int argc, char* argv[])
{
  if (argc != gorkova::arguments_count)
  {
    std::cerr << "ERROR: invalid number of arguments" << '\n';
    return gorkova::argument_error;
  }
  const std::string mode = argv[1];
  const std::string input_file = argv[2];
  const std::string output_file = argv[3];
  if ((mode != gorkova::stack_mode) && (mode != gorkova::heap_mode))
  {
    std::cerr << "First parameter is out of range" << '\n';
    return gorkova::argument_error;
  }
  std::ifstream in(input_file);
  if (!in)
  {
    std::cerr << "Cannot open input file" << '\n';
    return gorkova::data_error;
  }
  int rows = 0;
  int cols = 0;
  if (!gorkova::readSizes(in, rows, cols))
  {
    std::cerr << "Invalid sizes or matrix too large" << '\n';
    return gorkova::data_error;
  }
  std::ofstream out(output_file);
  if (!out)
  {
    std::cerr << "Cannot open output file" << '\n';
    return gorkova::data_error;
  }
  int result = 0;
  if (mode == gorkova::stack_mode)
  {
    int matrix[gorkova::max_size];
    if (!gorkova::readToStack(in, matrix, rows, cols))
    {
      std::cerr << "Bad matrix element" << '\n';
      return gorkova::data_error;
    }
    result = gorkova::countColumnsStack(matrix, rows, cols);
  }
  else
  {
    int** matrix = nullptr;
    try
    {
      matrix = gorkova::allocateMatrix(rows, cols);
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Cannot allocate matrix" << '\n';
      return gorkova::data_error;
    }
    if (!gorkova::readToDyn(in, matrix, rows, cols))
    {
      std::cerr << "Bad matrix element" << '\n';
      gorkova::freeMatrix(matrix, rows);
      return gorkova::data_error;
    }
    result = gorkova::countColumnsDyn(matrix, rows, cols);
    gorkova::freeMatrix(matrix, rows);
  }
  out << result << '\n';
  if (!out)
  {
    std::cerr << "Write failed" << '\n';
    return gorkova::data_error;
  }
  return 0;
}

