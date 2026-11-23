#include "ellipse.hpp"
#include <stdexcept>

const double PI = 3.14159265358979323846;

namespace kazbanov {
  Ellipse::Ellipse(double radiusX, double radiusY, const point_t& center):
    radiusX_(radiusX),
    radiusY_(radiusY),
    center_(center)
  {
    if (radiusX_ <= 0.0 || radiusY_ <= 0.0) {
      throw std::invalid_argument("ellipse radius should be greater than 0");
    }
  }

  double Ellipse::getArea() const
  {
    return PI * radiusX_ * radiusY_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    return {2.0 * radiusX_, 2.0 * radiusY_, center_};
  }

  void Ellipse::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Ellipse::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Ellipse::scale(double factor)
  {
    if (factor <= 0.0) {
      throw std::invalid_argument("factor must be positive");
    }
    radiusX_ *= factor;
    radiusY_ *= factor;
  }
}
