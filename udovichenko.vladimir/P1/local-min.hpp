#ifndef LOCAL_MIN_HPP
#define LOCAL_MIN_HPP
#include "sequence-property.hpp"

namespace udovichenko
{
  class LocalMinSeqProperty: public ISeqProperty
  {
  public:
    LocalMinSeqProperty() = default;

  private:
    std::size_t total_elements_{0};
    std::size_t count_{0};
    int prev_{0};
    int prev_prev_{0};

    std::size_t result() const override;
    void next(int i) noexcept override;
  };
}
#endif
