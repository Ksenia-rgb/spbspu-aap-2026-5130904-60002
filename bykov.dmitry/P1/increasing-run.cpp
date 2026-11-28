#include "increasing-run.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>

bykov::IncreasingRunCounter::IncreasingRunCounter():
  previous_(0),
  has_previous_(false),
  length_(0),
  maximum_(0)
{}

void bykov::IncreasingRunCounter::next(int next)
{
  if (next == 0)
  {
    throw std::invalid_argument("Zero is not a sequence element");
  }
  if (has_previous_ && next >= previous_)
  {
    if (length_ == std::numeric_limits< std::size_t >::max())
    {
      throw std::overflow_error("MON-INC: counter overflow");
    }
    ++length_;
  }
  else
  {
    length_ = 1;
  }
  if (length_ > maximum_)
  {
    maximum_ = length_;
  }
  previous_ = next;
  has_previous_ = true;
}

std::size_t bykov::IncreasingRunCounter::result() const
{
  return maximum_;
}
