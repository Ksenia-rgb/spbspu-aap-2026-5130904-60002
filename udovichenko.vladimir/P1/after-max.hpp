#ifndef AFTER_MAX_HPP
#define AFTER_MAX_HPP
#include "sequence-property.hpp"

namespace udovichenko
{
  class AfterMaxSeqProperty: public ISeqProperty
  {
  public:
    AfterMaxSeqProperty() = default;

  private:
    std::size_t total_elements_{0};
    std::size_t count_{0};
    int max_value_{0};

    std::size_t result() const override;
    void next(int i) noexcept override;
  };
}
#endif
