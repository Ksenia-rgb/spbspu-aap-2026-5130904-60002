#include "rectangle.hpp"
#include <stdexcept>

zelpus::Rectangle::Rectangle(const point_t & center, double width, double height):
  rect_{width, height, center}
{
  if (width <= 0.0 || height <= 0.0)
  {
    throw std::invalid_argument("Error: sides must be positive!\n");
  }
}

double zelpus::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

zelpus::rectangle_t zelpus::Rectangle::getFrameRect() const
{
  return rect_;
}

void zelpus::Rectangle::move(const point_t & p)
{
  rect_.pos = p;
}

void zelpus::Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void zelpus::Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("Error: scale factor must be positive!\n");
  }
  rect_.width *= k;
  rect_.height *= k;
}

