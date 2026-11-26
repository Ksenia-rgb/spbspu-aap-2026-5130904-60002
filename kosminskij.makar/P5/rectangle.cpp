#include "rectangle.hpp"

#include <stdexcept>

namespace kosminskij {
  Rectangle::Rectangle(const point_t& center, double width, double height):
    rect_{width, height, center}
  {
    if (width <= 0.0 || height <= 0.0) {
      throw std::invalid_argument("Rectangle: width and height must be positive");
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

  void Rectangle::move(const point_t& p)
  {
    rect_.pos = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    rect_.pos.x += dx;
    rect_.pos.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0) {
      throw std::invalid_argument("Rectangle: scale factor must be positive");
    }
    rect_.width *= k;
    rect_.height *= k;
  }
}
