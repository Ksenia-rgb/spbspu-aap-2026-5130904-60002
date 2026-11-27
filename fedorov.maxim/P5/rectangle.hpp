#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace fedorov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(point_t center, double height, double width);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_pos) override;
    void move(double delta_x, double delta_y) override;
    void scale(double factor) override;

  private:
    point_t center_;
    double height_;
    double width_;
  };
}

#endif
