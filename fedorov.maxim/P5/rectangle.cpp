#include <stdexcept>

#include "rectangle.hpp"

namespace fedorov
{
  Rectangle::Rectangle(const point_t center, const double height, const double width):
    center_(center),
    height_(height),
    width_(width)
  {
    if (height <= 0 || width <= 0)
    {
      throw std::invalid_argument("Height and width must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return height_ * width_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {height_, width_, center_};
  }

  void Rectangle::move(const point_t new_pos)
  {
    center_ = new_pos;
  }

  void Rectangle::move(const double delta_x, const double delta_y)
  {
    center_.x += delta_x;
    center_.y += delta_y;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor must be positive");
    }

    height_ *= factor;
    width_ *= factor;
  }
}
