#include "diamond.hpp"
#include <stdexcept>

namespace
{
  const double two = 2.0;
}

zelpus::Diamond::Diamond(const point_t &center, double horizDiag, double vertDiag):
  center_(center),
  horiz_(horizDiag),
  vert_(vertDiag)
{
  if (horiz_ <= 0.0 || vert_ <= 0.0)
  {
    throw std::invalid_argument("Error: sizes must be positive!\n");
  }
}

double zelpus::Diamond::getArea() const
{
  return horiz_ * vert_ / two;
}

zelpus::rectangle_t zelpus::Diamond::getFrameRect() const
{
  return {horiz_, vert_, center_};
}

void zelpus::Diamond::move(const point_t &p)
{
  center_ = p;
}

void zelpus::Diamond::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zelpus::Diamond::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("Error: scale factor must be positive!\n");
  }
  horiz_ *= k;
  vert_ *= k;
}
