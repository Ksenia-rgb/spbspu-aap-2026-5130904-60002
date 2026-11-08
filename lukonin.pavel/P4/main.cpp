#include <iostream>

namespace lukonin
{
  int isUnique(const char* const str, const int len) noexcept
  {
    for (int i = 0; i < len - 1; i++)
    {
      for (int j = i + 1; j < len; j++)
      {
        if (str[i] == str[j])
        {
          return 1;
        }
      }
    }

    return 0;
  }

  int haveCommon(const char* const str1, const int len1, const char* const str2, const int len2) noexcept
  {
    for (int i = 0; i < len1; i++)
    {
      for (int j = 0; j < len2; j++)
      {
        if (str1[i] == str2[j])
        {
          return 1;
        }
      }
    }

    return 0;
  }
}

int main()
{
  char c{};
  char* str = nullptr;
  int len = 0;

  try
  {
    while (std::cin.get(c))
    {
      if (c == '\n')
      {
        break;
      }

      char* new_str = new char[len + 2];
      for (int i = 0; i < len; i++)
      {
        new_str[i] = str[i];
      }
      new_str[len] = c;
      len++;
      new_str[len] = '\0';

      delete[] str;
      str = new_str;
      new_str = nullptr;
    }
  }
  catch (...)
  {
    std::cerr << "Error\n";
    return 1;
  }

  if (len == 0)
  {
    std::cerr << "Error\n";
    return 1;
  }

  std::cout << lukonin::isUnique(str, len) << "\n";

  char str2[4] = "abc";
  const int len2 = 3;

  std::cout << lukonin::haveCommon(str, len, str2, len2) << "\n";

  delete[] str;

  return 0;
}
