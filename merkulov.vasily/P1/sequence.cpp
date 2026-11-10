#include "sequence.hpp"
#include <cctype>
#include <istream>
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
      const int next = input.peek();
      const bool at_end = next == std::char_traits< char >::eof();
      if (!at_end && !std::isspace(static_cast< unsigned char >(next))) {
        throw std::invalid_argument("Sequence elements must be integers separated by whitespace");
      }
      if (input.bad()) {
        throw std::invalid_argument("Failed to read the sequence");
      }
      return value;
    }
  }
}

merkulov::sequence_stats_t merkulov::readSequence(std::istream & input)
{
  sequence_stats_t result = {0, 0, false, false, false};
  std::size_t equal_length = 0;
  int previous = 0;
  int before_previous = 0;
  bool has_two_elements = false;

  int current = detail::readInteger(input);
  while (current != 0) {
    if (result.has_elements && (current == previous)) {
      if (!detail::incrementCounter(equal_length)) {
        result.equal_overflow = true;
      }
    } else {
      const std::size_t single_element_length = 1;
      equal_length = single_element_length;
    }
    if (equal_length > result.longest_equal) {
      result.longest_equal = equal_length;
    }
    if (has_two_elements && (previous < before_previous) && (previous < current)) {
      if (!detail::incrementCounter(result.local_minima)) {
        result.minima_overflow = true;
      }
    }
    before_previous = previous;
    previous = current;
    has_two_elements = result.has_elements;
    result.has_elements = true;
    current = detail::readInteger(input);
  }
  return result;
}
