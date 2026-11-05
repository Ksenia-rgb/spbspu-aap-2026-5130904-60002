#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace shakirov
{
  constexpr std::size_t MAX_ROWS = 100;
  constexpr std::size_t MAX_COLS = 100;

  int **allocateMatrix(int rows, int cols)
  {
    if (rows <= 0 || cols <= 0)
    {
      throw std::invalid_argument("matrix size <= 0");
    }
    int **const matrix = new int *[rows];
    try
    {
      for (int i = 0; i < rows; ++i)
      {
        matrix[i] = new int[cols]{};
      }
    }
    catch (...)
    {
      for (int i = 0; i < rows; i++)
      {
        delete[] matrix[i];
      }
      delete[] matrix;
      throw;
    }
    return matrix;
  }

  void freeMatrix(int **matrix, int rows)
  {
    for (int i = 0; i < rows; i++)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  bool osedlElement(int **matrix, int row, int col, int rows, int cols)
  {
    const int element = matrix[row][col];
    for (int i = 0; i < rows; i++)
    {
      if (element < matrix[i][col])
      {
        return false;
      }
    }
    for (int i = 0; i < cols; i++)
    {
      if (element > matrix[row][i])
      {
        return false;
      }
    }
    return true;
  }

  bool osedlElement(int matrix[][MAX_COLS], int row, int col, int rows, int cols)
  {
    const int element = matrix[row][col];
    for (int i = 0; i < rows; i++)
    {
      if (element < matrix[i][col])
      {
        return false;
      }
    }
    for (int i = 0; i < cols; i++)
    {
      if (element > matrix[row][i])
      {
        return false;
      }
    }
    return true;
  }

  std::size_t checkCount(int **matrix, int rows, int cols)
  {
    std::size_t count = 0;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (osedlElement(matrix, i, j, rows, cols))
        {
          count++;
        }
      }
    }
    return count;
  }

  std::size_t checkCount(int matrix[][MAX_COLS], int rows, int cols)
  {
    std::size_t count = 0;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (osedlElement(matrix, i, j, rows, cols))
        {
          count++;
        }
      }
    }
    return count;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " <variant> <input> <output>\n";
    return 1;
  }
  const std::string in_name = argv[2];
  const std::string out_name = argv[3];
  const int variant = std::atoi(argv[1]);

  if (variant != 1 && variant != 2)
  {
    std::cerr << "Unsupported mode: " << variant << " (expected 1 or 2)\n";
    return 1;
  }

  std::ifstream fin(in_name);
  if (!fin)
  {
    std::cerr << "Cannot open input file: " << in_name << '\n';
    return 1;
  }

  std::size_t rows = 0, cols = 0;
  if (!(fin >> rows >> cols))
  {
    std::cerr << "Invalid matrix size in input file\n";
    return 1;
  }

  std::ofstream fout(out_name);
  if (!fout)
  {
    std::cerr << "Cannot open output file: " << out_name << '\n';
    return 1;
  }

  if (rows == 0 || cols == 0)
  {
    fout << 0 << '\n';
    return 0;
  }

  if (variant == 1)
  {
    if (rows > shakirov::MAX_ROWS || cols > shakirov::MAX_COLS)
    {
      std::cerr << "Matrix is too large for stack mode\n";
      return 1;
    }
    int matrix[shakirov::MAX_ROWS][shakirov::MAX_COLS];
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        if (!(fin >> matrix[i][j]))
        {
          std::cerr << "Not enough matrix elements in input file\n";
          return 1;
        }
      }
    }
    const std::size_t count = shakirov::checkCount(matrix, rows, cols);
    fout << count << '\n';
  }
  else
  {
    int **const matrix = shakirov::allocateMatrix(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        if (!(fin >> matrix[i][j]))
        {
          std::cerr << "Not enough matrix elements in input file\n";
          shakirov::freeMatrix(matrix, rows);
          return 1;
        }
      }
    }
    const std::size_t count = shakirov::checkCount(matrix, rows, cols);
    fout << count << '\n';
    shakirov::freeMatrix(matrix, rows);
  }
  return 0;
}
