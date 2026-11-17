#include "input.hpp"
#include <cstddef>
#include <cstring>
#include <istream>
#include <limits>
#include <stdexcept>

std::unique_ptr< char[] > merkulov::readLine(std::istream & input)
{
  const std::size_t initial_capacity = 128;
  std::size_t capacity = initial_capacity;
  std::unique_ptr< char[] > buffer(new char[capacity]);
  std::size_t length = 0;
  char symbol = 0;
  while (input.get(symbol)) {
    if (symbol == '\n') {
      buffer[length] = '\0';
      return buffer;
    }
    if (symbol == '\0') {
      throw std::runtime_error("A null character cannot be part of a C string");
    }
    if (length == capacity - 1) {
      const std::size_t growth_factor = 2;
      if (capacity > std::numeric_limits< std::size_t >::max() / growth_factor) {
        throw std::length_error("The line is too long");
      }
      const std::size_t new_capacity = capacity * growth_factor;
      std::unique_ptr< char[] > replacement(new char[new_capacity]);
      std::memcpy(replacement.get(), buffer.get(), length);
      buffer.swap(replacement);
      capacity = new_capacity;
    }
    buffer[length] = symbol;
    ++length;
  }
  if (input.bad() || !input.eof() || (length == 0)) {
    throw std::runtime_error("Failed to read a line");
  }
  buffer[length] = '\0';
  return buffer;
}
