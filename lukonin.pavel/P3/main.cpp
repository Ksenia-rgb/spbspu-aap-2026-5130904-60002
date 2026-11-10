#include <iostream>
#include <fstream>
#include <cstring>

void deleteMatr(int **&matr, int m)
{
  for (int i = 0; i < m; i++)
  {
    delete[] matr[i];
  }
  delete[] matr;
  matr = nullptr;
}

const int MAX_SIZE = 100;

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }

  std::ifstream file_i(argv[2]);
  if (!file_i)
  {
    std::cerr << "INVALID_INPUT_FILE\n";
    return 1;
  }
  int m{}, n{};
  if (!(file_i >> m >> n))
  {
    std::cerr << "INVALID_DATA\n";
    return 1;
  }

  if ((m == 0) && (n == 0))
  {
    file_i.close();

    std::ofstream file_o(argv[3]);
    file_o << 0;
    file_o.close();

    return 0;
  }
  else if ((m <= 0) || (n <= 0))
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }

  if (std::strcmp(argv[1], "1") == 0)
  {
    if ((n > MAX_SIZE) || (m > MAX_SIZE))
    {
      std::cerr << "INVALID_DATA\n";
      return 1;
    }
    int matr[MAX_SIZE][MAX_SIZE]{};
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (!(file_i >> matr[i][j]))
        {
          std::cerr << "INVALID_DATA\n";
          return 1;
        }
      }
    }

    file_i.close();

    int ans = 0;

    for (int i = 0; i < m; i++)
    {
      bool flag = true;
      for (int j = 0; j < n - 1; j++)
      {
        if (matr[i][j] == matr[i][j + 1])
        {
          flag = false;
        }
      }
      if (flag)
      {
        ans++;
      }
    }

    std::ofstream file_o(argv[3]);
    file_o << ans;
    file_o.close();
  }
  else if (std::strcmp(argv[1], "2") == 0)
  {
    int **matr = new int *[m];
    for (int i = 0; i < m; i++)
    {
      matr[i] = new int[n]{};
    }

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (!(file_i >> matr[i][j]))
        {
          std::cerr << "INVALID_DATA\n";
          deleteMatr(matr, m);
          return 1;
        }
      }
    }

    file_i.close();

    int ans = 0;

    for (int i = 0; i < m; i++)
    {
      bool flag = true;
      for (int j = 0; j < n - 1; j++)
      {
        if (matr[i][j] == matr[i][j + 1])
        {
          flag = false;
        }
      }
      if (flag)
      {
        ans++;
      }
    }

    deleteMatr(matr, m);

    std::ofstream file_o(argv[3]);
    file_o << ans;

    file_o.close();
  }
  else
  {
    std::cerr << "INVALID_ARGUMENT\n";
    return 1;
  }

  return 0;
}
