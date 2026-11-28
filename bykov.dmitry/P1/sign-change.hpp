#ifndef SIGN_CHANGE_HPP
#define SIGN_CHANGE_HPP
#include <cstddef>
#include "sequence-property.hpp"

namespace bykov
{
  class SignChangeCounter: public ISeqProperty
  {
  public:
    SignChangeCounter();

  private:
    int previous_;
    bool has_previous_;
    std::size_t changes_;

    void next(int value) override;
    std::size_t result() const override;
  };
}

#endif
