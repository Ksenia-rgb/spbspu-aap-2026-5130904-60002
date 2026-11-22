#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <new>

namespace chenin
{
  char *readLine(std::istream &in, std::size_t &size)
  {
    const std::size_t START_CAPACITY = 16;
    std::size_t capacity = START_CAPACITY;
    char *str = new char[capacity];
    size = 0;
    char symbol = '\0';
    while (in.get(symbol) && symbol != '\n')
    {
      if (size + 1 == capacity)
      {
        const std::size_t new_capacity = capacity * 2;
        char *temp = nullptr;
        try
        {
          temp = new char[new_capacity];
        }
        catch (const std::bad_alloc &)
        {
          delete[] str;
          throw;
        }
        for (std::size_t i = 0; i < size; ++i)
        {
          temp[i] = str[i];
        }
        delete[] str;
        str = temp;
        capacity = new_capacity;
      }
      str[size] = symbol;
      ++size;
    }
    str[size] = '\0';
    return str;
  }

  int hasRepeatedChars(const char *str)
  {
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
      if (std::strchr(str + i + 1, str[i]) != nullptr)
      {
        return 1;
      }
    }
    return 0;
  }

  int hasRepeatedDigits(const char *str)
  {
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
      const unsigned char symbol = static_cast< unsigned char >(str[i]);
      if (std::isdigit(symbol) && std::strchr(str + i + 1, str[i]) != nullptr)
      {
        return 1;
      }
    }
    return 0;
  }
}

int main()
{
  const int MEMORY_ERROR = 1;
  const int EMPTY_INPUT = 2;
  std::size_t size = 0;
  char *str = nullptr;
  try
  {
    str = chenin::readLine(std::cin, size);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: not enough memory\n";
    return MEMORY_ERROR;
  }
  if (size == 0)
  {
    delete[] str;
    std::cerr << "Error: empty input\n";
    return EMPTY_INPUT;
  }
  std::cout << chenin::hasRepeatedDigits(str) << "\n";
  std::cout << chenin::hasRepeatedChars(str) << "\n";
  delete[] str;
  return 0;
}
