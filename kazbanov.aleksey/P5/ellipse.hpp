#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"

namespace kazbanov
{
  class Ellipse: public Shape
  {
  public:
    Ellipse(double radius_x, double radius_y, const point_t& center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double radius_x_;
    double radius_y_;
    point_t center_;
  };
} // namespace kazbanov

#endif
