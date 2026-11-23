#ifndef P5_ELLIPSE_H
#define P5_ELLIPSE_H
#include "shape.hpp"

namespace kazbanov {
  class Ellipse: public Shape {
  public:
    Ellipse(double radiusX, double radiusY, const point_t& center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double radiusX_;
    double radiusY_;
    point_t center_;
  };
}

#endif
