#include "rectangle.hpp"
#include <stdexcept>

namespace ketov
{
  Rectangle::Rectangle(rectangle_t rect):
    rect_(rect)
  {
    if (rect_.width <= 0.0 || rect_.height <= 0.0)
    {
      throw std::invalid_argument("width and height must be greater than 0");
    }
  }

  double Rectangle::getArea() const
  {
    return rect_.width * rect_.height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rect_;
  }

  void Rectangle::move(point_t new_pos)
  {
    rect_.pos = new_pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    rect_.pos.x += dx;
    rect_.pos.y += dy;
  }

  void Rectangle::scale(double factor)
  {
    if (factor <= 0.0)
    {
      throw std::invalid_argument("factor must be greater than 0");
    }
    rect_.width *= factor;
    rect_.height *= factor;
  }
}
