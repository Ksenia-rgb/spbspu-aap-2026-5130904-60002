#include "rectangle.hpp"

#include <cmath>
#include <stdexcept>

const double two = 2.0;

namespace kazbanov {
  Rectangle::Rectangle(double width, double height, const point_t& center):
    rect_{width, height, center}
  {
    if (width <= 0.0 || height <= 0.0) {
      throw std::invalid_argument("Invalid rectangle width or height");
    }
  }

  Rectangle::Rectangle(const point_t& p1, const point_t& p2):
    rect_{std::abs(p1.x - p2.x), std::abs(p1.y - p2.y), {(p1.x + p2.x) / two, (p1.y + p2.y) / two}}
  {
    if (rect_.width <= 0.0 || rect_.height <= 0.0) {
      throw std::invalid_argument("Invalid rectangle width or height");
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

  void Rectangle::move(const point_t& new_pos)
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
    if (factor <= 0.0) {
      throw std::invalid_argument("factor must be positive");
    }
    rect_.width *= factor;
    rect_.height *= factor;
  }
} // namespace kazbanov
