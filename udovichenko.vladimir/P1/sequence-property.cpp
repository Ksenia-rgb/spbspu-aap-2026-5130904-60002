#include "sequence-property.hpp"

namespace udovichenko
{
  std::size_t ISeqProperty::operator()() const
  {
    return result();
  }

  void ISeqProperty::operator()(int i) noexcept
  {
    return next(i);
  }
}
