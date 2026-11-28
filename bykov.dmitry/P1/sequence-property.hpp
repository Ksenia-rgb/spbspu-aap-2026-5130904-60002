#ifndef SEQUENCE_PROPERTY_HPP
#define SEQUENCE_PROPERTY_HPP
#include <cstddef>

namespace bykov
{
  class ISeqProperty
  {
  public:
    virtual ~ISeqProperty() = default;
    std::size_t operator()() const;
    void operator()(int value);

  private:
    virtual std::size_t result() const = 0;
    virtual void next(int value) = 0;
  };
}

#endif
