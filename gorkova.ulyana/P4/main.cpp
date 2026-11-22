#include <iostream>
#include <cctype>
#include <cstddef>
#include <new>
#include <cstring>

namespace gorkova
{
  const int input_error = 1;
  const int duplicates_found = 1;
  const std::size_t initial_capacity = 16;
  char* readLine(std::size_t& size)
  {
    std::size_t capacity = initial_capacity;
    char* buffer = nullptr;
    try
    {
      buffer = new char[capacity];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Cannot allocate buffer" << '\n';
      return nullptr;
    }
    size = 0;
    char ch = '\0';
    while (std::cin.get(ch) && ch != '\n')
    {
      if (size + 1 >= capacity)
      {
        const std::size_t new_capacity = capacity * 2;
        char* new_buffer = nullptr;
        try
        {
          new_buffer = new char[new_capacity];
        }
        catch (const std::bad_alloc&)
        {
          std::cerr << "Cannot reallocate buffer" << '\n';
          delete[] buffer;
          return nullptr;
        }
        for (std::size_t i = 0; i < size; ++i)
        {
          new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        capacity = new_capacity;
      }
      buffer[size] = ch;
      ++size;
    }
    if (std::cin.bad())
    {
      std::cerr << "Input failed" << '\n';
      delete[] buffer;
      return nullptr;
    }
    buffer[size] = '\0';
    return buffer;
  }
  int hasAdjacentDuplicates(const char* const str)
  {
    if ((str == nullptr) || (str[0] == '\0'))
    {
      return 0;
    }
    for (std::size_t i = 0; str[i + 1] != '\0'; ++i)
    {
      if (str[i] == str[i + 1])
      {
        return duplicates_found;
      }
    }
    return 0;
  }
  char* appendDigits(char* const dest, const char* const str, const char* const digits)
  {
    std::size_t idx = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
      dest[idx] = str[i];
      ++idx;
    }
    for (std::size_t i = 0; digits[i] != '\0'; ++i)
    {
      if (std::isdigit(static_cast< unsigned char >(digits[i])) != 0)
      {
        dest[idx] = digits[i];
        ++idx;
      }
    }
    dest[idx] = '\0';
    return dest;
  }
}
int main()
{
  std::size_t first_size = 0;
  char* const first = gorkova::readLine(first_size);
  if (first == nullptr)
  {
    return gorkova::input_error;
  }
  if (first_size == 0)
  {
    std::cerr << "ERROR: empty input line" << '\n';
    delete[] first;
    return gorkova::input_error;
  }
  const char* const second = "g1h2k";
  const std::size_t second_size = std::strlen(second);
  std::cout << gorkova::hasAdjacentDuplicates(first) << '\n';
  const std::size_t result_size = first_size + second_size + 1;
  char* result = nullptr;
  try
  {
    result = new char[result_size];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Cannot allocate result buffer" << '\n';
    delete[] first;
    return gorkova::input_error;
  }
  gorkova::appendDigits(result, first, second);
  std::cout << result << '\n';
  delete[] result;
  delete[] first;
  return 0;
}
