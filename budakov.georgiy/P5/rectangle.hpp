#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace budakov
{
  class Rectangle : public Shape
  {
    double width_;
    double height_;
    point_t center_;

  public:
    Rectangle(const double width, const double height, const point_t& center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& target) noexcept override;
    void move(const double mv_x, const double mv_y) noexcept override;
    void scale(const double factor) override;

  };
}

#endif
