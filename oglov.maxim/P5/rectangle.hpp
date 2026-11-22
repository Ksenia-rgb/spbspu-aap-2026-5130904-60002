#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"
#include <iostream>
#include <stdexcept>
class Rectangle: public Shape
{
public:
  Rectangle(double w, double h, point_t pos):
    w_(w),
    h_(h),
    pos_(pos)
  {
    if (w <= 0.0 || h <= 0.0)
    {
      throw std::invalid_argument("Invalid argument( <= 0 )");
    }
  }
  double getArea() const override
  {
    return w_ * h_;
  }
  rectangle_t getFrameRect() const override
  {
    rectangle_t rec{w_, h_, pos_};
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
    w_ = w_ * k;
    h_ = h_ * k;
  }
private:
  double w_;
  double h_;
  point_t pos_;
};
#endif
