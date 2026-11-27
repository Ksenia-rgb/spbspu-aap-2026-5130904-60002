#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cstddef>

#include "base-types.hpp"
#include "shape.hpp"

namespace fedorov
{
  void scaleRelative(Shape* shape, point_t point, double factor);
  rectangle_t getFrameRectFromPoints(point_t* points, size_t size);
  double getShapesArea(Shape** shapes, size_t size);
  rectangle_t getShapesFrameRect(Shape** shapes, size_t size);
}

#endif
