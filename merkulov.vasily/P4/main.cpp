#include <cstring>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include "input.hpp"
#include "string.hpp"

int main()
{
  try {
    const std::unique_ptr< char[] > input = merkulov::readLine(std::cin);
    const char second[] = "def ";
    const std::size_t first_length = std::strlen(input.get());
    const std::size_t second_length = std::strlen(second);
    if (first_length > std::numeric_limits< std::size_t >::max() - second_length - 1) {
      throw std::length_error("The result is too long");
    }
    const std::unique_ptr< char[] > result(new char[first_length + second_length + 1]);
    merkulov::interleave(result.get(), input.get(), second);
    std::cout << merkulov::hasAdjacentEqual(input.get()) << '\n' << result.get() << '\n';
    std::cout.flush();
    if (!std::cout) {
      throw std::runtime_error("Failed to write the results");
    }
  } catch (const std::exception & error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
