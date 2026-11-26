#include "rectangle.hpp"

#include <stdexcept>

namespace korotkin
{
  Rectangle::Rectangle(double width, double height, point_t center):
    width_(width),
    height_(height),
    center_(center)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("ERROR: size must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t{width_, height_, center_};
  }

  void Rectangle::move(point_t p)
  {
    center_ = p;
  }

  void Rectangle::move(double x, double y)
  {
    center_.x += x;
    center_.y += y;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("ERROR: scale must be positive");
    }

    width_ *= k;
    height_ *= k;
  }
}
