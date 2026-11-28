#include "after-max.hpp"
#include <stdexcept>

namespace udovichenko
{
  std::size_t AfterMaxSeqProperty::result() const
  {
    if (total_elements_ == 0)
    {
      throw std::invalid_argument("Not enough elements to calculate count after maximum");
    }
    return count_;
  }

  void AfterMaxSeqProperty::next(int i) noexcept
  {
    count_++;
    if (total_elements_ == 0 || i > max_value_)
    {
      count_ = 0;
      max_value_ = i;
    }
    total_elements_++;
  }
}
