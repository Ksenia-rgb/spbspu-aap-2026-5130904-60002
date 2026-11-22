#ifndef XQUARE_HPP
#define XQUARE_HPP
#include "base-types.hpp"
#include "shape.hpp"
#include <stdexcept>
class Xquare: public Shape
{
public:
  Xquare(double d, point_t pos):
    d_(d),
    pos_(pos)
  {
    if (d <= 0.0)
    {
      throw std::invalid_argument("Invalid argument( <= 0 )");
    }
  }
  double getArea() const override
  {
    return (d_ * d_) / 2;
  }
  rectangle_t getFrameRect() const override
  {
    rectangle_t rec{d_, d_, pos_};
    return rec;
  }
  void move(const point_t& point) override
  {
    pos_ = point;
  }
  void move(double dx, double dy) override
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void scale(double k) override
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid argument( <= 0 )");
    }
    d_ = d_ * k;
  }
private:
  double d_;
  point_t pos_;
};
#endif
