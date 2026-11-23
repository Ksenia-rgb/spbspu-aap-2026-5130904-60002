#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace borovkov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double w, double h, const point_t& pos);
    Rectangle(const point_t& p1, const point_t& p2);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double x, double y) override;
    void scale(double factor) override;

  private:
    double width_;
    double height_;
    point_t center_;
  };
}

#endif
