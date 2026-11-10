#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstddef>
#include <iosfwd>

namespace merkulov {
  struct sequence_stats_t {
    std::size_t longestEqual;
    std::size_t localMinima;
    bool hasElements;
    bool equalOverflow;
    bool minimaOverflow;
  };

  sequence_stats_t readSequence(std::istream & input);
}

#endif
