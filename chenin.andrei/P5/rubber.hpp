#ifndef RUBBER_HPP
#define RUBBER_HPP

#include "shape.hpp"

namespace chenin
{
  class Rubber: public Shape
  {
  public:
    Rubber(const point_t &in_pos, double in_r, const point_t &out_pos, double out_r);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t inner_center_;
    double inner_radius_;
    point_t outer_center_;
    double outer_radius_;
  };
}

#endif
