#ifndef RING_HPP
#define RING_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace bykov
{
  class Ring: public Shape
  {
  public:
    Ring(point_t center, double inner_radius, double outer_radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t position) override;
    void move(double dx, double dy) override;

  protected:
    void scaleUnsafely(double factor) override;

  private:
    point_t center_;
    double inner_radius_;
    double outer_radius_;
  };
}

#endif
