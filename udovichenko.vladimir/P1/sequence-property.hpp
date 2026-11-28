#ifndef SEQUENCE_PROPERTY_HPP
#define SEQUENCE_PROPERTY_HPP
#include <cstddef>

namespace udovichenko
{
  class ISeqProperty
  {
  public:
    std::size_t operator()() const;
    void operator()(int i) noexcept;
    virtual ~ISeqProperty() = default;

  private:
    virtual std::size_t result() const = 0;
    virtual void next(int i) noexcept = 0;
  };
}
#endif
