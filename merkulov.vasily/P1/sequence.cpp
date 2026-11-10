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
      const bool atEnd = next == std::char_traits< char >::eof();
      if (!atEnd && !std::isspace(static_cast< unsigned char >(next))) {
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
  std::size_t equalLength = 0;
  int previous = 0;
  int beforePrevious = 0;
  bool hasTwoElements = false;

  int current = detail::readInteger(input);
  while (current != 0) {
    if (result.hasElements && (current == previous)) {
      if (!detail::incrementCounter(equalLength)) {
        result.equalOverflow = true;
      }
    } else {
      const std::size_t singleElementLength = 1;
      equalLength = singleElementLength;
    }
    if (equalLength > result.longestEqual) {
      result.longestEqual = equalLength;
    }
    if (hasTwoElements && (previous < beforePrevious) && (previous < current)) {
      if (!detail::incrementCounter(result.localMinima)) {
        result.minimaOverflow = true;
      }
    }
    beforePrevious = previous;
    previous = current;
    hasTwoElements = result.hasElements;
    result.hasElements = true;
    current = detail::readInteger(input);
  }
  return result;
}
