#include "ellipse.hpp"

#include <stdexcept>

const double PI = 3.14159265358979323846;
const double two = 2.0;

namespace kazbanov
{
  Ellipse::Ellipse(double radius_x, double radius_y, const point_t& center):
    radius_x_(radius_x),
    radius_y_(radius_y),
    center_(center)
  {
    if (radius_x_ <= 0.0 || radius_y_ <= 0.0)
    {
      throw std::invalid_argument("ellipse radius should be greater than 0");
    }
  }

  double Ellipse::getArea() const
  {
    return PI * radius_x_ * radius_y_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    return {two * radius_x_, two * radius_y_, center_};
  }

  void Ellipse::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Ellipse::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Ellipse::scale(double factor)
  {
    if (factor <= 0.0)
    {
      throw std::invalid_argument("factor must be positive");
    }
    radius_x_ *= factor;
    radius_y_ *= factor;
  }
} // namespace kazbanov
