#include "shape.hpp"
#include <stdexcept>

namespace udovichenko
{
  void IShape::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid shape scale");
    }
    scaleUnsafely(factor);
  }
}
