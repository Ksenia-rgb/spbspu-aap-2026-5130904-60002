#include "diamond.hpp"
#include <stdexcept>

namespace udovichenko
{
  Diamond::Diamond(double diagonal_x, double diagonal_y, const point_t &center):
    diagonal_x_(diagonal_x),
    diagonal_y_(diagonal_y),
    center_(center)
  {
    if (diagonal_x <= 0 || diagonal_y <= 0)
    {
      throw std::invalid_argument("Diamond diagonals must be positive numbers");
    }
  }

  double Diamond::getArea() const
  {
    return diagonal_x_ * diagonal_y_ / 2;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {diagonal_x_, diagonal_y_, center_};
  }

  void Diamond::move(const point_t &p)
  {
    center_ = p;
  }

  void Diamond::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  IShape *Diamond::clone() const
  {
    return new Diamond(*this);
  }

  void Diamond::scaleUnsafely(double factor) noexcept
  {
    diagonal_x_ *= factor;
    diagonal_y_ *= factor;
  }
}
