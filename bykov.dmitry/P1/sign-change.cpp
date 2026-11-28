#include "sign-change.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>

bykov::SignChangeCounter::SignChangeCounter():
  previous_(0),
  has_previous_(false),
  changes_(0)
{}

void bykov::SignChangeCounter::next(int next)
{
  if (next == 0)
  {
    throw std::invalid_argument("Zero is not a sequence element");
  }
  if (has_previous_ && ((next < 0) != (previous_ < 0)))
  {
    if (changes_ == std::numeric_limits< std::size_t >::max())
    {
      throw std::overflow_error("SGN-CHG: counter overflow");
    }
    ++changes_;
  }
  previous_ = next;
  has_previous_ = true;
}

std::size_t bykov::SignChangeCounter::result() const
{
  return changes_;
}
