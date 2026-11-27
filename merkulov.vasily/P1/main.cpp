#include <iostream>
#include <stdexcept>
#include "sequence.hpp"

int main()
{
  try {
    return merkulov::processSequence(std::cin, std::cout, std::cerr);
  } catch (const std::invalid_argument & error) {
    const int input_error = 1;
    std::cerr << error.what() << '\n';
    return input_error;
  }
}
