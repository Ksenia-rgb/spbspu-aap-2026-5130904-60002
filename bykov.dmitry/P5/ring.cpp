#include "ring.hpp"
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"
#include "geometry.hpp"

bykov::Ring::Ring(point_t center, double inner_radius, double outer_radius):
  center_(center),
  inner_radius_(inner_radius),
  outer_radius_(outer_radius)
{
  checkPositive(inner_radius_);
  checkPositive(outer_radius_);
  if (inner_radius_ >= outer_radius_)
  {
    throw std::invalid_argument("The inner radius must be smaller than the outer radius");
  }
  checkFrame(getFrameRect());
  getArea();
}

double bykov::Ring::getArea() const
{
  const double pi = std::acos(-1.0);
  const double area = pi * (outer_radius_ - inner_radius_) * (outer_radius_ + inner_radius_);
  if (!std::isfinite(area) || area <= 0.0)
  {
    throw std::overflow_error("The ring area cannot be represented");
  }
  return area;
}

bykov::rectangle_t bykov::Ring::getFrameRect() const
{
  constexpr double diameter_factor = 2.0;
  const double diameter = outer_radius_ * diameter_factor;
  return {diameter, diameter, center_};
}

void bykov::Ring::move(point_t position)
{
  rectangle_t next = getFrameRect();
  next.pos = position;
  checkFrame(next);
  center_ = position;
}

void bykov::Ring::move(double dx, double dy)
{
  move(shiftPoint(center_, dx, dy));
}

void bykov::Ring::scale(double factor)
{
  checkPositive(factor);
  const Ring scaled(center_, inner_radius_ * factor, outer_radius_ * factor);
  inner_radius_ = scaled.inner_radius_;
  outer_radius_ = scaled.outer_radius_;
}
