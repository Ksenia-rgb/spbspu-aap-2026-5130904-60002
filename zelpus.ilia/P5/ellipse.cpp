#include "ellipse.hpp"
#include <stdexcept>

namespace
{
  const double two = 2.0;
  const double PI = 3.141593;
}

zelpus::Ellipse::Ellipse(const point_t &center, double radiusX, double radiusY):
  center_(center),
  rx_(radiusX),
  ry_(radiusY)
{
  if (rx_ <= 0.0 || ry_ <= 0.0)
  {
    throw std::invalid_argument("Error: radiuses must be positive!\n");
  }
}

double zelpus::Ellipse::getArea() const
{
  return PI * rx_ * ry_;
}

zelpus::rectangle_t zelpus::Ellipse::getFrameRect() const
{
  return {two * rx_, two * ry_, center_};
}

void zelpus::Ellipse::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zelpus::Ellipse::move(const point_t &p)
{
  center_ = p;
}

void zelpus::Ellipse::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("Error: scale factor must be positive!\n");
  }
  rx_ *= k;
  ry_ *= k;
}
