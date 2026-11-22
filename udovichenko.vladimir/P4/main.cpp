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

    size_t result_len = 0;
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
      if (std::strchr(str2, str1[i]))
      {
        buf[result_len++] = str1[i];
      }
    }

    buf[result_len] = '\0';
    return result_len;
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
  const char *const STRING_FOR_COMMON_SYMBOLS = "abc ef";
  const char *const STRING_FOR_HAS_SAME = "abs";
  std::string input_string;
  try
  {
    if (!std::getline(std::cin, input_string))
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

  const size_t length = input_string.length();
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
  udovichenko::getCommonSymbolsString(input_string.c_str(), STRING_FOR_COMMON_SYMBOLS, result);
  std::cout << result << '\n';
  delete[] result;
  result = nullptr;

  std::cout << udovichenko::hasSameChars(input_string.c_str(), STRING_FOR_HAS_SAME) << '\n';

  return 0;
}
