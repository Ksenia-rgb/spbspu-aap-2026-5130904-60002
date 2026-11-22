#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {
  constexpr double eps = 1e-9;
  constexpr double half = 0.5;
  constexpr double two = 2.0;
  constexpr double three = 3.0;
}

namespace ketov {
  Triangle::Triangle(point_t p1, point_t p2, point_t p3):
    p1_(p1),
    p2_(p2),
    p3_(p3)
  {
    if (getArea() < eps) {
      throw std::invalid_argument("invalid argument");
    }
  }

  double Triangle::getArea() const
  {
    return half * std::abs((p2_.x - p1_.x) * (p3_.y - p1_.y) - (p3_.x - p1_.x) * (p2_.y - p1_.y));
  }

  rectangle_t Triangle::getFrameRect() const
  {
    const double x_max = std::max({p1_.x, p2_.x, p3_.x});
    const double y_max = std::max({p1_.y, p2_.y, p3_.y});
    const double x_min = std::min({p1_.x, p2_.x, p3_.x});
    const double y_min = std::min({p1_.y, p2_.y, p3_.y});

    return {x_max - x_min, y_max - y_min, {(x_max + x_min) / two, (y_max + y_min) / two}};
  }

  void Triangle::move(point_t new_pos)
  {
    const point_t pos{(p1_.x + p2_.x + p3_.x) / three, (p1_.y + p2_.y + p3_.y) / three};
    move(new_pos.x - pos.x, new_pos.y - pos.y);
  }

  void Triangle::move(double dx, double dy)
  {
    p1_.x += dx;
    p1_.y += dy;
    p2_.x += dx;
    p2_.y += dy;
    p3_.x += dx;
    p3_.y += dy;
  }

  void Triangle::scale(double factor)
  {
    if (factor <= 0.0) {
      throw std::invalid_argument("invalid argument");
    }
    const point_t pos{(p1_.x + p2_.x + p3_.x) / three, (p1_.y + p2_.y + p3_.y) / three};

    p1_.x = pos.x + (p1_.x - pos.x) * factor;
    p1_.y = pos.y + (p1_.y - pos.y) * factor;
    p2_.x = pos.x + (p2_.x - pos.x) * factor;
    p2_.y = pos.y + (p2_.y - pos.y) * factor;
    p3_.x = pos.x + (p3_.x - pos.x) * factor;
    p3_.y = pos.y + (p3_.y - pos.y) * factor;
  }
}
