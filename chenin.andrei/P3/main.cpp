#include <iostream>
#include <cstring>
#include <fstream>

namespace chenin
{
  bool isLowerTriangular(const int *a, size_t rows, size_t cols)
  {
    size_t n = rows;
    if (cols < rows)
    {
      n = cols;
    }
    if (n == 0)
    {
      return false;
    }
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        if (a[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }
}

int main(int argc, char **argv)
{
  const size_t MAX_SIZE = 10000;
  int matrix[MAX_SIZE] = {};
  size_t rows = 0, cols = 0;
  int *data = matrix;
  const int WRONG_ARGS = 1;
  const int WRONG_INPUT = 2;
  if (argc != 4)
  {
    std::cerr << "Wrong number of arguments" << "\n";
    return WRONG_ARGS;
  }

  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
  {
    std::cerr << "Wrong first argument" << "\n";
    return WRONG_ARGS;
  }
  int num = 1;
  if (std::strcmp(argv[1], "2") == 0)
  {
    num = 2;
  }

  std::ifstream input(argv[2]);

  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "Wrong input" << "\n";
    return WRONG_INPUT;
  }
  if (num == 1 && cols * rows > MAX_SIZE)
  {
    std::cerr << "Wrong input" << "\n";
    return WRONG_INPUT;
  }
  if (num == 2)
  {
    data = new int[rows * cols];
  }
  for (size_t k = 0; k < rows * cols; ++k)
  {
    input >> data[k];
    if (!input)
    {
      if (num == 2)
      {
        delete[] data;
      }
      std::cerr << "Wrong input" << "\n";
      return WRONG_INPUT;
    }
  }

  std::ofstream output(argv[3]);
  if (chenin::isLowerTriangular(data, rows, cols))
  {
    output << "true" << "\n";
  }
  else
  {
    output << "false" << "\n";
  }

  if (num == 2)
  {
    delete[] data;
  }
  return 0;
}
