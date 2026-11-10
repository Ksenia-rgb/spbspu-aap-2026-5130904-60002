#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstddef>
#include <iosfwd>

namespace merkulov {
  struct sequence_stats_t {
    std::size_t longest_equal;
    std::size_t local_minima;
    bool has_elements;
    bool equal_overflow;
    bool minima_overflow;
  };

  sequence_stats_t readSequence(std::istream & input);
}

#endif
