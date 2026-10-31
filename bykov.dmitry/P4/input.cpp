#include "input.hpp"
#include <cstddef>
#include <cstring>
#include <istream>
#include <limits>
#include <stdexcept>

char* bykov::readLine(std::istream& input)
{
  const std::size_t initial_capacity = 32;
  const std::size_t growth_factor = 2;
  std::size_t capacity = initial_capacity;
  std::size_t length = 0;
  char* buffer = new char[capacity];
  try
  {
    char character = '\0';
    while (input.get(character))
    {
      if (character == '\n')
      {
        buffer[length] = '\0';
        return buffer;
      }
      if (character == '\0')
      {
        delete[] buffer;
        return nullptr;
      }
      if (length == capacity - 1)
      {
        if (capacity > std::numeric_limits< std::size_t >::max() / growth_factor)
        {
          throw std::overflow_error("The input line is too long");
        }
        const std::size_t new_capacity = capacity * growth_factor;
        char* const expanded = new char[new_capacity];
        std::memcpy(expanded, buffer, length);
        delete[] buffer;
        buffer = expanded;
        capacity = new_capacity;
      }
      buffer[length] = character;
      ++length;
    }
    if (input.bad() || !input.eof() || length == 0)
    {
      delete[] buffer;
      return nullptr;
    }
    buffer[length] = '\0';
    return buffer;
  }
  catch (...)
  {
    delete[] buffer;
    throw;
  }
}
