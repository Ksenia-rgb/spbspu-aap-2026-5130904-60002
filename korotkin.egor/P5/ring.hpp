#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

namespace korotkin
{
  class Ring: public Shape
  {
  public:
    Ring(double outerRadius, double innerRadius, point_t center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double x, double y) override;
    void scale(double k) override;

  private:
    double outerRadius_;
    double innerRadius_;
    point_t center_;
  };
}

#endif
