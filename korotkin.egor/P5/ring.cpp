#include "ring.hpp"

#include <stdexcept>

namespace
{
  const double PI = 3.14159265358979323846;
}

namespace korotkin
{
  Ring::Ring(double outer_radius, double inner_radius, point_t center):
    outer_radius_(outer_radius),
    inner_radius_(inner_radius),
    center_(center)
  {
    if (outer_radius <= 0 || inner_radius <= 0)
    {
      throw std::invalid_argument("ERROR: radius must be positive");
    }

    if (outer_radius <= inner_radius)
    {
      throw std::invalid_argument("ERROR: outer radius > inner radius");
    }
  }

  double Ring::getArea() const
  {
    return PI * (outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_);
  }

  rectangle_t Ring::getFrameRect() const
  {
    return rectangle_t{2 * outer_radius_, 2 * outer_radius_, center_};
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

    outer_radius_ *= k;
    inner_radius_ *= k;
  }
}

