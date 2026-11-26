#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>

#include "shape.hpp"
#include "base-types.hpp"

namespace fedorov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t center, const double height, const double width):
      center_(center),
      height_(height),
      width_(width)
    {
      if (height <= 0 || width <= 0)
      {
        throw std::invalid_argument("Height and width must be positive");
      }
    }

    double getArea() const override
    {
      return height_ * width_;
    }

    rectangle_t getFrameRect() const override
    {
      return {height_, width_, center_};
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
      height_ *= factor;
      width_ *= factor;
    }
  private:
    point_t center_;
    double height_;
    double width_;
  };
}

#endif
