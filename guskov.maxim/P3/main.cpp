#include <cstdlib>
#include <fstream>
#include <iostream>

namespace guskov
{
  const int MAX_SIZE = 10000;
  const int DECIMAL_BASE = 10;

  bool readMatrix(std::istream& in, int* const data, long long total)
  {
    for (long long i = 0; i < total; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  int countRowsNoEqual(const int* data, int rows, int cols)
  {
    int count = rows;
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 1; j < cols; ++j)
      {
        if (data[i * cols + j] == data[i * cols + j - 1])
        {
          --count;
          break;
        }
      }
    }
    return count;
  }
}

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
  const long num = std::strtol(argv[1], &end, guskov::DECIMAL_BASE);
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

  long long rows = 0;
  long long cols = 0;
  in >> rows >> cols;
  if (((!in) || rows < 0) || cols < 0)
  {
    std::cerr << "Invalid arguments matrix\n";
    return 2;
  }

  const long long total = rows * cols;
  int fixed_data[guskov::MAX_SIZE];
  int* heap_data = nullptr;
  int* data = fixed_data;

  if (num == 1)
  {
    if (cols > guskov::MAX_SIZE || rows > guskov::MAX_SIZE || total > guskov::MAX_SIZE)
    {
      std::cerr << "Matrix is too large\n";
      return 2;
    }
  }
  else
  {
    try
    {
      heap_data = new int[total];
    }
    catch (...)
    {
      std::cerr << "Can't allocate memory\n";
      return 2;
    }
    data = heap_data;
  }

  if (!guskov::readMatrix(in, data, total))
  {
    delete[] heap_data;
    std::cerr << "Invalid arguments matrix\n";
    return 2;
  }

  const int count = guskov::countRowsNoEqual(data, rows, cols);
  delete[] heap_data;

  std::ofstream out(argv[3]);
  if (!out)
  {
    std::cerr << "Can't open output file: " << argv[3] << '\n';
    return 1;
  }

  out << count << "\n";
  return 0;
}
