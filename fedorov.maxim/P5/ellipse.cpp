#include <stdexcept>

#include "ellipse.hpp"
#include "base-types.hpp"

namespace fedorov
{
  const double PI = 3.1415926535897932;

  Ellipse::Ellipse(const point_t center, const double radius_x, const double radius_y):
    center_(center),
    radius_x_(radius_x),
    radius_y_(radius_y)
  {
    if (radius_x <= 0 || radius_y <= 0)
    {
      throw std::invalid_argument("Radius X and Radius Y must be positive");
    }
  }

  double Ellipse::getArea() const
  {
    return PI * radius_x_ * radius_y_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    return {2 * radius_y_, 2 * radius_x_, center_};
  }

  void Ellipse::move(const point_t new_pos)
  {
    center_ = new_pos;
  }

  void Ellipse::move(const double delta_x, const double delta_y)
  {
    center_.x += delta_x;
    center_.y += delta_y;
  }

  void Ellipse::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor must be positive");
    }
    radius_x_ *= factor;
    radius_y_ *= factor;
  }
}
