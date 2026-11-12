#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  char* end = nullptr;
  const long num = std::strtol(argv[1], &end, 10);
  if (end == argv[1] || *end != '\0')
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "Can't open input file: " << argv[2] << '\n';
    return 1;
  }

  int rows = 0;
  int cols = 0;
  in >> rows >> cols;
  if (((!in) || rows < 0) || cols < 0)
  {
    std::cerr << "Invalid arguments matrix\n";
    return 2;
  }
  int count = rows;
  const int MAX_SIZE = 10000;
  int data[MAX_SIZE];
  if (num == 1)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        in >> data[j];
        if (!in)
        {
          std::cerr << "Invalid arguments matrix\n";
          return 2;
        }
      }

      for (int j = 1; j < cols; ++j)
      {
        if (data[j] == data[j - 1])
        {
          --count;
          break;
        }
      }
    }
  }
  if (num == 2)
  {
    int** const matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
    {
      matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        in >> matrix[i][j];
        if (!in)
        {
          std::cerr << "Invalid arguments matrix\n";

          for (int i = 0; i < rows; ++i)
          {
            delete[] matrix[i];
          }
          delete[] matrix;
          return 2;
        }
      }
    }

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 1; j < cols; ++j)
      {
        if (matrix[i][j] == matrix[i][j - 1])
        {
          --count;
          break;
        }
      }
    }

    for (int i = 0; i < rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  std::ofstream out(argv[3]);
  if (!out)
  {
    std::cerr << "Can't open output file: " << argv[3] << '\n';
    return 1;
  }

  out << count << "\n";
  return 0;
}
