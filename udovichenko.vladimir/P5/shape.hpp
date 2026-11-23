#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace udovichenko
{
  class IShape
  {
  public:
    virtual ~IShape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &p) = 0;
    virtual void move(double dx, double dy) = 0;
    void scale(double factor);

  protected:
    virtual void scaleUnsafely(double factor) = 0;
  };
}

#endif
