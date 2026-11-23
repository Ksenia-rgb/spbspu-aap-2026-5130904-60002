#ifndef P5_SHAPE_H
#define P5_SHAPE_H
#include "base-types.h"

namespace kazbanov {
  class Shape {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& newPos) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
  };
} // namespace kazbanov

#endif
