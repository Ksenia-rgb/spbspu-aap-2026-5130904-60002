#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace udovichenko
{
  class Rectangle: public IShape
  {
  public:
    Rectangle(double width, double height, const point_t &center);
    Rectangle(const point_t &a, const point_t &b);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(double dx, double dy) override;

  protected:
    void scaleUnsafely(double factor) override;

  private:
    double width_;
    double height_;
    point_t center_;
  };
}

#endif
