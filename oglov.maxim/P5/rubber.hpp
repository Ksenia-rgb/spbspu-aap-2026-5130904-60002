#ifndef RUBBER_HPP
#define RUBBER_HPP
#include "base-types.hpp"
#include "shape.hpp"
#include <stdexcept>
#include <cmath>
class Rubber: public Shape
{
public:
  Rubber(double r_b, point_t pos_b, double r_s, point_t pos_s):
    r_b_(r_b),
    pos_b_(pos_b),
    r_s_(r_s),
    pos_s_(pos_s)
  {
    if ((r_b <= 0.0 || r_s <= 0.0) || (pos_b.x == pos_s.x && pos_b.y == pos_s.y))
    {
      throw std::invalid_argument("Raiduses mus be positive or postion is soos");
    }
    double d = std::sqrt((pos_b.x - pos_s.x) * (pos_b.x - pos_s.x) + (pos_b.y - pos_s.y) * (pos_b.y - pos_s.y));
    if (r_b <= r_s || (d * d > (r_b - r_s) * (r_b - r_s)))
    {
      throw std::invalid_argument("Small circle not in big circle");
    }
  }
  double getArea() const override
  {
    double pi = 3.141592;
    return (r_b_ * r_b_ * pi) - (r_s_ * r_s_ * pi);
  }
  rectangle_t getFrameRect() const override
  {
    rectangle_t rec{r_b_ * 2, r_b_ * 2, pos_b_};
    return rec;
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
    double dx = point.x - pos_s_.x;
    double dy = point.y - pos_s_.y;
    move(dx, dy);
  }

  void scale(double k) override
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid argument( <= 0 )");
    }
    r_s_ *= k;
    double dx = pos_b_.x - pos_s_.x;
    double dy = pos_b_.y - pos_s_.y;
    pos_b_ = {pos_b_.x + dx * k, pos_b_.y + dy * k};
    r_b_ *= k;
  }
private:
  double r_b_;
  point_t pos_b_;
  double r_s_;
  point_t pos_s_;
};
#endif
