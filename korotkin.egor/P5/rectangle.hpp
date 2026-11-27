#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace korotkin
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, point_t center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double x, double y) override;
    void scale(double k) override;

  private:
    double width_;
    double height_;
    point_t center_;
  };
}

#endif
