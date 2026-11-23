#include "ring.hpp"

#include <stdexcept>

namespace borovkov
{
  const double PI = 3.141592653589793;

  Ring::Ring(double r_out, double r_in, const point_t& pos):
    radius_out_(r_out),
    radius_in_(r_in),
    center_(pos)
  {
    if (r_in <= 0 || r_out <= 0)
    {
      throw std::invalid_argument("Incorrect input. Radius must be positive");
    }
    if (r_in >= r_out)
    {
      throw std::invalid_argument("Incorrect input. Out radius must be bigger than in radius");
    }
  }

  double Ring::getArea() const
  {
    return radius_out_ * radius_out_ * PI - radius_in_ * radius_in_ * PI;
  }

  rectangle_t Ring::getFrameRect() const
  {
    return {2 * radius_out_, 2 * radius_out_, center_};
  }

  void Ring::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Ring::move(double x, double y)
  {
    center_.x += x;
    center_.y += y;
  }

  void Ring::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Incorrect input. Factor must be positive");
    }
    radius_out_ *= factor;
    radius_in_ *= factor;
  }
}
