#ifndef COMPLEXQUAD_HPP
#define COMPLEXQUAD_HPP

#include <stdexcept>
#include "shape.hpp"

namespace budakov
{
  class Complexquad : public Shape
  {
    point_t p[4];
    point_t center_;
    bool crossed_type_;

  public:
    Complexquad(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& p4);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& target) noexcept override;
    void move(const double mv_x, const double mv_y) noexcept override;
    void scale(const double factor) override;
  };
}
#endif