#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace udovichenko
{
  class Triangle: public IShape
  {
  public:
    Triangle(const point_t &a, const point_t &b, const point_t &c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t a_;
    point_t b_;
    point_t c_;
    point_t center_;

    double calcArea() const;
  };
}
#endif
