#ifndef RUBBER_HPP
#define RUBBER_HPP

#include "shape.hpp"

namespace kosminskij
{

  class Rubber: public Shape
  {
  public:
    Rubber(const point_t& center, double inner_radius, const point_t& outer_center, double outer_radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t center_;
    point_t outer_center_;
    double inner_radius_;
    double outer_radius_;
  };
}

#endif
