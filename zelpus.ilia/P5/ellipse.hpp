#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"

namespace zelpus
{

  class Ellipse final: public Shape
  {
  public:
    Ellipse(const point_t & center, double radiusX, double radiusY);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    point_t center_;
    double rx_;
    double ry_;
  };
}

#endif
