#include "triangle.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace udovichenko
{
  Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):
    a_(a),
    b_(b),
    c_(c)
  {
    center_ = {(a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3};
    if (calcArea() <= 0.0)
    {
      throw std::invalid_argument("Invalid triangle");
    }
  }

  double Triangle::getArea() const
  {
    return calcArea();
  }

  rectangle_t Triangle::getFrameRect() const
  {
    const double max_x = std::max({a_.x, b_.x, c_.x});
    const double max_y = std::max({a_.y, b_.y, c_.y});
    const double min_x = std::min({a_.x, b_.x, c_.x});
    const double min_y = std::min({a_.y, b_.y, c_.y});
    return {max_x - min_x, max_y - min_y, {(max_x + min_x) / 2, (max_y + min_y) / 2}};
  }

  void Triangle::move(const point_t &p)
  {
    move(p.x - center_.x, p.y - center_.y);
  }

  void Triangle::move(double dx, double dy)
  {
    a_.x += dx;
    a_.y += dy;
    b_.x += dx;
    b_.y += dy;
    c_.x += dx;
    c_.y += dy;
    center_.x += dx;
    center_.y += dy;
  }

  IShape *Triangle::clone() const
  {
    return new Triangle(*this);
  }

  void Triangle::scaleUnsafely(double factor) noexcept
  {
    a_.x = center_.x + (a_.x - center_.x) * factor;
    a_.y = center_.y + (a_.y - center_.y) * factor;
    b_.x = center_.x + (b_.x - center_.x) * factor;
    b_.y = center_.y + (b_.y - center_.y) * factor;
    c_.x = center_.x + (c_.x - center_.x) * factor;
    c_.y = center_.y + (c_.y - center_.y) * factor;
  }

  double Triangle::calcArea() const
  {
    return std::abs((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) / 2;
  }
}
