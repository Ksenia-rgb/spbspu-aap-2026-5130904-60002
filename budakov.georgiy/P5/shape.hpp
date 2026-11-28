#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace budakov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& target) noexcept = 0;
    virtual void move(const double mv_x, const double mv_y) noexcept = 0;
    virtual void scale(const double factor) = 0;
  };
}

#endif
