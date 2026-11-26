#ifndef SHAPE_FUNCTIONS_HPP
#define SHAPE_FUNCTIONS_HPP
#include "composite-shape.hpp"

namespace udovichenko
{
  void printShapes(const CompositeShape &shapes);
  void allotropicScaleShapes(CompositeShape &shapes, const point_t &point, double factor);
}

#endif
