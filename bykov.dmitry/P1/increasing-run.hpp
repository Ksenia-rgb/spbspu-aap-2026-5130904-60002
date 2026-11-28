#ifndef INCREASING_RUN_HPP
#define INCREASING_RUN_HPP
#include <cstddef>
#include "sequence-property.hpp"

namespace bykov
{
  class IncreasingRunCounter: public ISeqProperty
  {
  public:
    IncreasingRunCounter();

  private:
    int previous_;
    bool has_previous_;
    std::size_t length_;
    std::size_t maximum_;

    void next(int value) override;
    std::size_t result() const override;
  };
}

#endif
