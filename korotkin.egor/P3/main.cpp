#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace korotkin
{
  void eraseMatrix(int** matrix, int rows);
}

void korotkin::eraseMatrix(int** matrix, int rows)
{
  if (matrix != nullptr)
  {
    for (int i = 0; i < rows; i++)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main(int argc, char* argv[])
{
  const int arg_err = 1;
  const int file_err = 2;

  const int max_rows = 100;
  const int max_cols = 100;

  if (argc < 4)
  {
    std::cerr << "ERROR: Not enough arguments\n";
    return arg_err;
  }

  if (argc > 4)
  {
    std::cerr << "ERROR: Too many arguments\n";
    return arg_err;
  }

  for (int i = 0; argv[1][i] != '\0'; i++)
  {
    if (argv[1][i] < '0' || argv[1][i] > '9')
    {
      std::cerr << "ERROR: First parameter is not a number\n";
      return arg_err;
    }
  }

  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
  {
    std::cerr << "ERROR: First parameter is out of range\n";
    return arg_err;
  }

  std::ifstream file_in(argv[2]);
  if (!file_in.is_open())
  {
    std::cerr << "ERROR: Cannot open read file\n";
    return file_err;
  }

  int rows = 0;
  int cols = 0;
  if (!(file_in >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "ERROR: Invalid size\n";
    return file_err;
  }

  int stack_matrix[max_rows][max_cols]{};
  int* stack_rows[max_rows]{};
  int** dyn_matrix = nullptr;
  int** matrix = nullptr;

  if (argv[1][0] == '1')
  {
    if (rows > max_rows || cols > max_cols)
    {
      std::cerr << "ERROR: Invalid size for stack matrix (Max size: 100 100)\n";
      return file_err;
    }

    for (int i = 0; i < rows; i++)
    {
      stack_rows[i] = stack_matrix[i];
    }
    matrix = stack_rows;
  }
  else if (argv[1][0] == '2')
  {
    try
    {
      dyn_matrix = new int* [rows] { };
      for (int i = 0; i < rows; i++)
      {
        dyn_matrix[i] = new int[cols];
      }
    }
    catch (...)
    {
      std::cerr << "ERROR: Cannot allocate memory\n";
      korotkin::eraseMatrix(dyn_matrix, rows);
      return file_err;
    }

    matrix = dyn_matrix;
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!(file_in >> matrix[i][j]))
      {
        std::cerr << "ERROR: Cannot read file\n";
        korotkin::eraseMatrix(dyn_matrix, rows);
        return file_err;
      }
    }
  }
  file_in.close();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      matrix[i][j] += std::min({i, j, rows - i - 1, cols - j - 1}) + 1;
    }
  }

  std::ofstream file_out(argv[3]);
  if (!file_out.is_open())
  {
    std::cerr << "ERROR: Cannot open output file\n";
    korotkin::eraseMatrix(dyn_matrix, rows);
    return file_err;
  }

  if (!(file_out << rows << ' ' << cols))
  {
    std::cerr << "ERROR: Cannot write to file\n";
    korotkin::eraseMatrix(dyn_matrix, rows);
    return file_err;
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!(file_out << ' ' << matrix[i][j]))
      {
        std::cerr << "ERROR: Cannot write to file\n";
        korotkin::eraseMatrix(dyn_matrix, rows);
        return file_err;
      }
    }
  }
  file_out << '\n';
  file_out.close();

  korotkin::eraseMatrix(dyn_matrix, rows);

  return 0;
}
