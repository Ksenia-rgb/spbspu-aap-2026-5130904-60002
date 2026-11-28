#include "rectangle.hpp"
#include <stdexcept>

namespace chenin
{
  Rectangle::Rectangle(double width, double height, const point_t &pos):
    width_(width),
    height_(height),
    pos_(pos)
  {
    if (width_ <= 0.0 || height_ <= 0.0)
    {
      throw std::invalid_argument("Rectangle sides must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, pos_};
  }

  void Rectangle::move(const point_t &pos)
  {
    pos_ = pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    width_ *= k;
    height_ *= k;
  }
}
