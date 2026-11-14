#include "sequence.hpp"
#include <cctype>
#include <cstddef>
#include <istream>
#include <ostream>
#include <limits>
#include <stdexcept>

namespace merkulov {
  namespace detail {
    static bool incrementCounter(std::size_t & counter)
    {
      if (counter == std::numeric_limits< std::size_t >::max()) {
        return false;
      }
      ++counter;
      return true;
    }

    static int readInteger(std::istream & input)
    {
      int value = 0;
      if (!(input >> value)) {
        throw std::invalid_argument("Expected an integer sequence terminated by zero");
      }
      if (input.eof()) {
        return value;
      }
      char separator = 0;
      if (!input.get(separator)) {
        if (input.bad() || !input.eof()) {
          throw std::invalid_argument("Failed to read the sequence");
        }
      } else if (!std::isspace(static_cast< unsigned char >(separator))) {
        throw std::invalid_argument("Sequence elements must be integers separated by whitespace");
      }
      return value;
    }
  }
}

int merkulov::processSequence(std::istream & input, std::ostream & output, std::ostream & errors)
{
  std::size_t longest_equal = 0;
  std::size_t local_minima = 0;
  bool has_elements = false;
  bool equal_overflow = false;
  bool minima_overflow = false;
  std::size_t equal_length = 0;
  int previous = 0;
  int before_previous = 0;
  bool has_two_elements = false;

  int current = detail::readInteger(input);
  while (current != 0) {
    if (has_elements && (current == previous)) {
      if (!detail::incrementCounter(equal_length)) {
        equal_overflow = true;
      }
    } else {
      const std::size_t single_element_length = 1;
      equal_length = single_element_length;
    }
    if (equal_length > longest_equal) {
      longest_equal = equal_length;
    }
    if (has_two_elements && (previous < before_previous) && (previous < current)) {
      if (!detail::incrementCounter(local_minima)) {
        minima_overflow = true;
      }
    }
    before_previous = previous;
    previous = current;
    has_two_elements = has_elements;
    has_elements = true;
    current = detail::readInteger(input);
  }
  const int calculation_error = 2;
  int exit_code = 0;
  if (equal_overflow) {
    errors << "EQL-SEQ: counter overflow\n";
    exit_code = calculation_error;
  } else {
    output << longest_equal << '\n';
  }
  if (!has_elements) {
    errors << "LOC-MIN: the sequence is empty\n";
    exit_code = calculation_error;
  } else if (minima_overflow) {
    errors << "LOC-MIN: counter overflow\n";
    exit_code = calculation_error;
  } else {
    output << local_minima << '\n';
  }
  if (!output) {
    errors << "Failed to write the results\n";
    return calculation_error;
  }
  return exit_code;
}
