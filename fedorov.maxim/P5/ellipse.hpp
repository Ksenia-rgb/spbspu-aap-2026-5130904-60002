#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <iostream>

#include "shape.hpp"
#include "base-types.hpp"

namespace fedorov
{
  const double PI = 3.1415926535897932;

  class Ellipse: public Shape
  {
  public:
    Ellipse(const point_t center, const double radius_x, const double radius_y):
      center_(center),
      radius_x_(radius_x),
      radius_y_(radius_y)
    {
      if (radius_x <= 0 || radius_y <= 0)
      {
        throw std::invalid_argument("Radius X and Radius Y must be positive");
      }
    }

    double getArea() const override
    {
      return PI * radius_x_ * radius_y_;
    }

    rectangle_t getFrameRect() const override
    {
      return {2 * radius_x_, 2 * radius_y_, center_};
    }

    void move(const point_t new_pos) override
    {
      center_ = new_pos;
    }

    void move(const double delta_x, const double delta_y) override
    {
      center_.x += delta_x;
      center_.y += delta_y;
    }

    void scale(const double factor) override
    {
      if (factor <= 0)
      {
        throw std::invalid_argument("Factor must be positive");
      }
      radius_x_ *= factor;
      radius_y_ *= factor;
    }
  private:
    point_t center_;
    double radius_x_;
    double radius_y_;
  };
}

#endif
