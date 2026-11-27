#ifndef CONCAVE_HPP
#define CONCAVE_HPP

#include "shape.hpp"
#include <cstddef>

namespace korotkin
{
  const std::size_t VERTICES_NUMBER = 4;

  class Concave: public Shape
  {
  public:
    Concave(point_t a, point_t b, point_t c, point_t d);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double x, double y) override;
    void scale(double k) override;

  private:
    point_t vertices_[VERTICES_NUMBER];

    double cross(point_t a, point_t b, point_t c) const;

    std::size_t getReflexIndex() const;
  };
}

#endif
