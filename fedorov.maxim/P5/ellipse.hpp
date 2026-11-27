#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace fedorov
{
  class Ellipse: public Shape
  {
  public:
    Ellipse(point_t center, double radius_x, double radius_y);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_pos) override;
    void move(double delta_x, double delta_y) override;
    void scale(double factor) override;
  private:
    point_t center_;
    double radius_x_;
    double radius_y_;
  };
}

#endif
