#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }
  
  std::ifstream file_i(argv[2]);
  int m, n;
  file_i >> m >> n;

  if ((m <= 0) && (n <= 0))
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }


  if (std::stoi(argv[1]) == 1)
  {
    if ((n > 100) || (m > 100))
    {
      std::cerr << "INVALID_DATA\n";
      return 1;
    }
    int matr[100][100]{};
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        file_i >> matr[i][j];
        std::cout << matr[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
  else if (std::stoi(argv[1]) == 2)
  {
    int** matr = new int*[m]{};
    for (int i = 0; i < m; i++)
    {
      matr[i] = new int[n]{};
    }

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        file_i >> matr[i][j];
        std::cout << matr[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
  else
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }

  return 0;
}