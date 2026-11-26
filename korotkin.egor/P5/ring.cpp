#include "ring.hpp"

#include <stdexcept>

namespace
{
  const double PI = 3.14159265358979323846;
}

namespace korotkin
{
  Ring::Ring(double outerRadius, double innerRadius, point_t center):
    outerRadius_(outerRadius),
    innerRadius_(innerRadius),
    center_(center)
  {
    if (outerRadius <= 0 || innerRadius <= 0)
    {
      throw std::invalid_argument("ERROR: radius must be positive");
    }

    if (outerRadius <= innerRadius)
    {
      throw std::invalid_argument("ERROR: outer radius > inner radius");
    }
  }

  double Ring::getArea() const
  {
    return PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
  }

  rectangle_t Ring::getFrameRect() const
  {
    return rectangle_t{2 * outerRadius_, 2 * outerRadius_, center_};
  }

  void Ring::move(point_t p)
  {
    center_ = p;
  }

  void Ring::move(double x, double y)
  {
    center_.x += x;
    center_.y += y;
  }

  void Ring::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("ERROR: scale must be positive");
    }

    outerRadius_ *= k;
    innerRadius_ *= k;
  }
}

