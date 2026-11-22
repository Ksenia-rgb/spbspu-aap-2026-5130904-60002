#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include "shape.hpp"

namespace udovichenko
{
  class Diamond: public IShape
  {
  public:
    Diamond(double diagonal_x, double diagonal_y, const point_t &center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double diagonal_x_;
    double diagonal_y_;
    point_t center_;
  };
}

#endif
