#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace zelpus
{
  class Rectangle final: public Shape
  {
  public:
    Rectangle(const point_t & center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    rectangle_t rect_;
  };
}

#endif
