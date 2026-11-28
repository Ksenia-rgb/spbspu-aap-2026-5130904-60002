#include <stdexcept>
#include "rectangle.hpp"

namespace budakov
{
  Rectangle::Rectangle(const double width, const double height, const point_t& center):
    width_(width),
    height_(height),
    center_(center)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Wrong size\n");
    }
  }
  
  double Rectangle::getArea() const
  {
    return width_*height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, center_};
  }

  void Rectangle::move(const point_t& target) noexcept
  {
    center_.x = target.x;
    center_.y = target.y;
  }

  void Rectangle::move(const double mv_x, const double mv_y) noexcept
  {
    center_.x += mv_x;
    center_.y += mv_y;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Wrong factor\n");
    }

    width_ *= factor;
    height_ *= factor;
  }
}