#include "sequence-property.hpp"
#include <cstddef>

std::size_t bykov::ISeqProperty::operator()() const
{
  return result();
}

void bykov::ISeqProperty::operator()(int value)
{
  next(value);
}
