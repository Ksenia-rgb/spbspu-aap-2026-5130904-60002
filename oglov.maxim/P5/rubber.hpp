#ifndef RUBBER_HPP
#define RUBBER_HPP

#include <cmath>
#include <stdexcept>

#include "base-types.hpp"
#include "shape.hpp"

namespace oglov
{
  constexpr double pi = 3.141592;
  constexpr double two = 2.0;
}

class Rubber: public Shape
{
public:
  Rubber(double r_b, point_t pos_b, double r_s, point_t pos_s):
    r_b_(r_b),
    pos_b_(pos_b),
    r_s_(r_s),
    pos_s_(pos_s)
  {
    if (r_b <= 0.0 || r_s <= 0.0)
    {
      throw std::invalid_argument("Rubber: radii must be positive");
    }
    if (pos_b.x == pos_s.x && pos_b.y == pos_s.y)
    {
      throw std::invalid_argument("Rubber: circles must not be concentric");
    }
    const double dx = pos_b.x - pos_s.x;
    const double dy = pos_b.y - pos_s.y;
    const double d2 = dx * dx + dy * dy;
    const double dr = r_b - r_s;
    if (r_b <= r_s || d2 > dr * dr)
    {
      throw std::invalid_argument("Rubber: small circle must be inside big");
    }
  }

  double getArea() const override
  {
    return oglov::pi * (r_b_ * r_b_ - r_s_ * r_s_);
  }

  rectangle_t getFrameRect() const override
  {
    return {r_b_ * oglov::two, r_b_ * oglov::two, pos_b_};
  }

  void move(double dx, double dy) override
  {
    pos_b_.x += dx;
    pos_b_.y += dy;
    pos_s_.x += dx;
    pos_s_.y += dy;
  }

  void move(const point_t& point) override
  {
    const double dx = point.x - pos_s_.x;
    const double dy = point.y - pos_s_.y;
    move(dx, dy);
  }

  void scale(double k) override
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Rubber::scale: k must be positive");
    }
    r_b_ *= k;
    r_s_ *= k;
    const double dx = pos_b_.x - pos_s_.x;
    const double dy = pos_b_.y - pos_s_.y;
    pos_b_.x = pos_s_.x + (dx)*k;
    pos_b_.y = pos_s_.y + (dy)*k;
  }

private:
  double r_b_;
  point_t pos_b_;
  double r_s_;
  point_t pos_s_;
};
#endif

