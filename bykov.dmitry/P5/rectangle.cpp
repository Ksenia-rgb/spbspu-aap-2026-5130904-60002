#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"
#include "geometry.hpp"

bykov::Rectangle::Rectangle(point_t center, double width, double height):
  frame_{width, height, center}
{
  checkFrame(frame_);
  getArea();
}

double bykov::Rectangle::getArea() const
{
  const double area = frame_.width * frame_.height;
  if (!std::isfinite(area) || area <= 0.0)
  {
    throw std::overflow_error("The area cannot be represented");
  }
  return area;
}

bykov::rectangle_t bykov::Rectangle::getFrameRect() const
{
  return frame_;
}

void bykov::Rectangle::move(point_t position)
{
  rectangle_t next = frame_;
  next.pos = position;
  checkFrame(next);
  frame_ = next;
}

void bykov::Rectangle::move(double dx, double dy)
{
  move(shiftPoint(frame_.pos, dx, dy));
}

void bykov::Rectangle::scale(double factor)
{
  const rectangle_t next = scaleFrame(frame_, factor);
  const Rectangle scaled(next.pos, next.width, next.height);
  frame_ = scaled.frame_;
}
