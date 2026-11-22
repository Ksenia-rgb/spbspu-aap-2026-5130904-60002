#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
struct Shape
{
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& point) = 0;
  virtual void move(const double dx, const double dy) = 0;
  virtual void scale(const double k) = 0;

  virtual ~Shape() = default;
};
#endif
