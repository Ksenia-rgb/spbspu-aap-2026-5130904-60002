#include "rectangle.hpp"

#include <stdexcept>
#include <cmath>

namespace borovkov
{
  Rectangle::Rectangle(double w, double h, const point_t& pos):
    width_(w),
    height_(h),
    center_(pos)
  {
    if (w <= 0 || h <= 0)
    {
      throw std::invalid_argument("Incorrect input. Width and height must be positive");
    }
  }

  Rectangle::Rectangle(const point_t& p1, const point_t& p2):
    width_(std::abs(p2.x - p1.x)),
    height_(std::abs(p2.y - p1.y)),
    center_({(p1.x + p2.x) / 2, (p1.y + p2.y) / 2})
  {
    if ((p1.x == p2.x) || (p1.y == p2.y))
    {
      throw std::invalid_argument("Incorrect input. Two points must be different");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, center_};
  }

  void Rectangle::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Rectangle::move(double x, double y)
  {
    center_.x += x;
    center_.y += y;
  }

  void Rectangle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Incorrect input. Factor must be positive");
    }
    width_ *= factor;
    height_ *= factor;
  }
}
