#ifndef RING_HPP
#define RING_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace borovkov
{
  class Ring: public Shape
  {
  public:
    Ring(double r_out, double r_in, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double x, double y) override;
    void scale(double factor) override;

  private:
    double radius_out_;
    double radius_in_;
    point_t center_;
  };
}

#endif
