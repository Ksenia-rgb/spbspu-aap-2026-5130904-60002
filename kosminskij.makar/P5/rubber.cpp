#include "rubber.hpp"

#include <cmath>
#include <stdexcept>

namespace kosminskij {
  namespace {
    const double kPi = 3.14159265358979323846;
  }

  Rubber::Rubber(const point_t& center,
      double innerRadius,
      const point_t& outerCenter,
      double outerRadius):
    center_(center),
    outerCenter_(outerCenter),
    innerRadius_(innerRadius),
    outerRadius_(outerRadius)
  {
    if (innerRadius <= 0.0 || outerRadius <= innerRadius) {
      throw std::invalid_argument("Rubber: need 0 < inner radius < outer radius");
    }
    const double dist = std::hypot(outerCenter.x - center.x, outerCenter.y - center.y);
    if (dist == 0.0) {
      throw std::invalid_argument("Rubber: circles must not be concentric");
    }
    if (dist + innerRadius >= outerRadius) {
      throw std::invalid_argument("Rubber: inner circle must lie strictly inside the outer one");
    }
  }

  double Rubber::getArea() const
  {
    return kPi * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
  }

  rectangle_t Rubber::getFrameRect() const
  {
    return {2.0 * outerRadius_, 2.0 * outerRadius_, outerCenter_};
  }

  void Rubber::move(const point_t& p)
  {
    move(p.x - center_.x, p.y - center_.y);
  }

  void Rubber::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
    outerCenter_.x += dx;
    outerCenter_.y += dy;
  }

  void Rubber::scale(double k)
  {
    if (k <= 0.0) {
      throw std::invalid_argument("Rubber: scale factor must be positive");
    }
    innerRadius_ *= k;
    outerRadius_ *= k;
    outerCenter_.x = center_.x + (outerCenter_.x - center_.x) * k;
    outerCenter_.y = center_.y + (outerCenter_.y - center_.y) * k;
  }
}
