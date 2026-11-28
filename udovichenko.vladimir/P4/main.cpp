#include <cstring>
#include <string>
#include <iostream>
#include <limits>
#include "ascii-string.hpp"

namespace udovichenko
{
  constexpr std::size_t INITIAL_CAPACITY = 64;

  ASCIIString getCommonSymbolsString(const ASCIIString &str1, const ASCIIString &str2)
  {
    ASCIIString result;
    for (size_t i = 0; i < str1.size(); i++)
    {
      if (std::strchr(str2.cStr(), str1[i]))
      {
        result.append(str1[i]);
      }
    }

    return result;
  }

  int hasSameChars(const ASCIIString &str1, const ASCIIString &str2)
  {
    for (size_t i = 0; i < str1.size(); i++)
    {
      if (std::strchr(str2.cStr(), str1[i]))
      {
        return 1;
      }
    }

    return 0;
  }

  bool readInputLine(std::istream &input, char *&buf, std::size_t &size)
  {
    delete[] buf;
    buf = nullptr;
    std::size_t capacity = INITIAL_CAPACITY;
    size = 0;
    buf = new char[capacity + 1];
    try
    {
      char ch = '\0';
      while (input.get(ch) && ch != '\n')
      {
        if (size + 1 > capacity)
        {
          if (capacity >= std::numeric_limits< std::size_t >::max() / 2)
          {
            throw std::length_error("Too many characters in input");
          }
          capacity *= 2;
          char *const temp = new char[capacity + 1];
          std::memcpy(temp, buf, size);
          delete[] buf;
          buf = temp;
        }
        buf[size] = ch;
        size++;
      }
      buf[size] = '\0';
    }
    catch (...)
    {
      delete[] buf;
      buf = nullptr;
      throw;
    }

    if (size == 0 && input.eof())
    {
      delete[] buf;
      buf = nullptr;
      return false;
    }
    return true;
  }

  bool readInputLine(std::istream &input, ASCIIString &string)
  {
    string.erase();
    char ch = '\0';
    while (input.get(ch) && ch != '\n')
    {
      string.append(ch);
    }

    if (string.size() == 0 && input.eof())
    {
      return false;
    }

    return true;
  }
}

int main()
{
  const udovichenko::ASCIIString COMMON_SYMBOLS_STR{"abc ef"};
  const udovichenko::ASCIIString HAS_SAME_STRING{"abs"};
  try
  {
    udovichenko::ASCIIString input_string;
    if (!udovichenko::readInputLine(std::cin, input_string))
    {
      std::cerr << "Failed to read string" << '\n';
      return 1;
    }
    const udovichenko::ASCIIString result = udovichenko::getCommonSymbolsString(input_string, COMMON_SYMBOLS_STR);
    std::cout << result.cStr() << '\n';
    std::cout << udovichenko::hasSameChars(input_string, HAS_SAME_STRING) << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << "Failed to read string: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
