#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <iosfwd>
#include <cstddef>
#include "base-types.hpp"

namespace bykov
{
  class Shape;

  void checkPoint(point_t point);
  void checkPositive(double value);
  void checkFrame(rectangle_t frame);
  point_t shiftPoint(point_t point, double dx, double dy);
  rectangle_t scaleFrame(rectangle_t frame, double factor);
  rectangle_t getTotalFrame(const Shape* const* shapes, std::size_t count);
  void scaleShapes(Shape* const* shapes, std::size_t count, point_t center, double factor);
  void printShapes(std::ostream& output, const Shape* const* shapes, std::size_t count);
}

#endif
