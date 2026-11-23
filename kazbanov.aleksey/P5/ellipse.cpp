#include "ellipse.hpp"

#include <stdexcept>

const double PI = 3.14159265358979323846;
const double two = 2.0;

namespace kazbanov {
  Ellipse::Ellipse(double radius_X, double radius_Y, const point_t& center):
    radius_X_(radius_X),
    radius_Y_(radius_Y),
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
    return {two * radiusX_, two * radiusY_, center_};
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
} // namespace kazbanov
