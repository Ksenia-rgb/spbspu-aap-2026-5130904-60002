#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include "shape.hpp"

namespace budakov
{
  class Bubble : public Shape
  {
    double radius_;
    double dx_;
    double dy_;
    point_t center_;

  public:
    Bubble(const double radius, const point_t& true_centre, const point_t& centre);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& target) noexcept override;
    void move(const double mv_x, const double mv_y) noexcept override;
    void scale(const double factor) override;
  };
}

#endif
