#ifndef P5_RECTANGLE_H
#define P5_RECTANGLE_H
#include "shape.hpp"

namespace kazbanov {
  class Rectangle: public Shape {
  public:
    Rectangle(double width, double height, const point_t& pos);
    Rectangle(const point_t& p1, const point_t& p2);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    rectangle_t rect_;
  };
}

#endif
