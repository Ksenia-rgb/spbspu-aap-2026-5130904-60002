#include <cstring>
#include <string>
#include <iostream>

namespace udovichenko
{
  size_t getCommonSymbolsString(const char *str1, const char *str2, char *buf)
  {
    if (!str1 || !str2 || !buf)
    {
      return 0;
    }

    size_t resultLen = 0;
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
      if (std::strchr(str2, str1[i]))
      {
        buf[resultLen++] = str1[i];
      }
    }

    buf[resultLen] = '\0';
    return resultLen;
  }

  int hasSameChars(const char *str1, const char *str2)
  {
    if (!str1 || !str2)
    {
      return 0;
    }

    for (size_t i = 0; str1[i] != '\0'; i++)
    {
      if (std::strchr(str2, str1[i]))
      {
        return 1;
      }
    }

    return 0;
  }

  char *allocateString(size_t length)
  {
    char *const buffer = new char[length + 1];
    buffer[length] = '\0';
    return buffer;
  }
}

int main()
{
  const char *const stringForCommonSymbols = "abc ef";
  const char *const stringForHasSame = "abs";
  std::string inputString;
  try
  {
    if (!std::getline(std::cin, inputString))
    {
      std::cerr << "Failed to read string" << '\n';
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to read string: " << e.what() << '\n';
    return 1;
  }

  const size_t length = inputString.length();
  char *result = nullptr;
  try
  {
    result = udovichenko::allocateString(length);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to allocate memory: " << e.what() << '\n';
    return 1;
  }
  udovichenko::getCommonSymbolsString(inputString.c_str(), stringForCommonSymbols, result);
  std::cout << result << '\n';
  delete[] result;
  result = nullptr;

  std::cout << udovichenko::hasSameChars(inputString.c_str(), stringForHasSame) << '\n';

  return 0;
}
