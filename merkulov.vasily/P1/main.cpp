#include <iostream>
#include <stdexcept>
#include "sequence.hpp"

int main()
{
  const int input_error = 1;
  const int calculation_error = 2;
  try {
    const merkulov::sequence_stats_t result = merkulov::readSequence(std::cin);
    int exit_code = 0;
    if (result.equal_overflow) {
      std::cerr << "EQL-SEQ: counter overflow\n";
      exit_code = calculation_error;
    } else {
      std::cout << result.longest_equal << '\n';
    }
    if (!result.has_elements) {
      std::cerr << "LOC-MIN: the sequence is empty\n";
      exit_code = calculation_error;
    } else if (result.minima_overflow) {
      std::cerr << "LOC-MIN: counter overflow\n";
      exit_code = calculation_error;
    } else {
      std::cout << result.local_minima << '\n';
    }
    if (!std::cout) {
      std::cerr << "Failed to write the results\n";
      return calculation_error;
    }
    return exit_code;
  } catch (const std::invalid_argument & error) {
    std::cerr << error.what() << '\n';
    return input_error;
  }
}
