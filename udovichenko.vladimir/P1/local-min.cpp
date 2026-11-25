#include "local-min.hpp"
#include <stdexcept>

namespace udovichenko
{
  std::size_t LocalMinSeqProperty::result() const
  {
    if (total_elements_ == 0)
    {
      throw std::invalid_argument("Not enough elements to calculate local minimum");
    }
    return count_;
  }

  void LocalMinSeqProperty::next(int i) noexcept
  {
    if (total_elements_ >= 2 && prev_ < prev_prev_ && prev_ < i)
    {
      count_++;
    }
    prev_prev_ = prev_;
    prev_ = i;
    total_elements_++;
  }
}
