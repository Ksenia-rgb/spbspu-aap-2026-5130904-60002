#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

namespace udovichenko
{
  Rectangle::Rectangle(double width, double height, const point_t &center):
    width_(width),
    height_(height),
    center_(center)
  {
    if (width_ <= 0.0 || height_ <= 0.0)
    {
      throw std::invalid_argument("Invalid rectangle width or height");
    }
  }

  Rectangle::Rectangle(const point_t &a, const point_t &b)
  {
    if (a.x == b.x || a.y == b.y)
    {
      throw std::invalid_argument("Can't make rectangle by 2 points on the same line");
    }

    width_ = std::abs(a.x - b.x);
    height_ = std::abs(a.y - b.y);
    center_ = {(a.x + b.x) / 2, (a.y + b.y) / 2};
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, center_};
  }

  void Rectangle::move(const point_t &p)
  {
    center_ = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  IShape *Rectangle::clone() const
  {
    return new Rectangle(*this);
  }

  void Rectangle::scaleUnsafely(double factor) noexcept
  {
    width_ *= factor;
    height_ *= factor;
  }
}
