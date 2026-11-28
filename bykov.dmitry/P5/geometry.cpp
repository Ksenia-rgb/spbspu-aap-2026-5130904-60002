#include "geometry.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>
#include <cstddef>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"

namespace bykov
{
  namespace
  {
    constexpr double half = 0.5;

    point_t scaledPosition(point_t position, point_t center, double factor)
    {
      const point_t result = {center.x + (position.x - center.x) * factor, center.y + (position.y - center.y) * factor};
      checkPoint(result);
      return result;
    }
  }
}

void bykov::checkPoint(point_t point)
{
  if (!std::isfinite(point.x) || !std::isfinite(point.y))
  {
    throw std::invalid_argument("Point coordinates must be finite");
  }
}

void bykov::checkPositive(double value)
{
  if (!std::isfinite(value) || value <= 0.0)
  {
    throw std::invalid_argument("A length or scale factor must be finite and positive");
  }
}

void bykov::checkFrame(rectangle_t frame)
{
  checkPoint(frame.pos);
  checkPositive(frame.width);
  checkPositive(frame.height);
  const double left = frame.pos.x - frame.width * half;
  const double right = frame.pos.x + frame.width * half;
  const double bottom = frame.pos.y - frame.height * half;
  const double top = frame.pos.y + frame.height * half;
  if (!std::isfinite(left) || !std::isfinite(right) || !std::isfinite(bottom) || !std::isfinite(top))
  {
    throw std::overflow_error("The frame coordinates overflow");
  }
}

bykov::point_t bykov::shiftPoint(point_t point, double dx, double dy)
{
  checkPoint({dx, dy});
  const point_t result = {point.x + dx, point.y + dy};
  checkPoint(result);
  return result;
}

void bykov::Shape::scale(double factor)
{
  checkPositive(factor);
  scaleUnsafely(factor);
}

bykov::rectangle_t bykov::getTotalFrame(const Shape* const* shapes, std::size_t count)
{
  if (count == 0)
  {
    throw std::invalid_argument("Cannot bound an empty array of shapes");
  }
  const rectangle_t first = shapes[0]->getFrameRect();
  double left = first.pos.x - first.width * half;
  double right = first.pos.x + first.width * half;
  double bottom = first.pos.y - first.height * half;
  double top = first.pos.y + first.height * half;
  for (std::size_t i = 1; i < count; ++i)
  {
    const rectangle_t frame = shapes[i]->getFrameRect();
    left = std::min(left, frame.pos.x - frame.width * half);
    right = std::max(right, frame.pos.x + frame.width * half);
    bottom = std::min(bottom, frame.pos.y - frame.height * half);
    top = std::max(top, frame.pos.y + frame.height * half);
  }
  const rectangle_t result = {right - left, top - bottom, {left * half + right * half, bottom * half + top * half}};
  checkFrame(result);
  return result;
}

void bykov::scaleShapes(Shape* const* shapes, std::size_t count, point_t center, double factor)
{
  checkPoint(center);
  if (factor == 1.0)
  {
    return;
  }
  for (std::size_t i = 0; i < count; ++i)
  {
    const point_t position = shapes[i]->getFrameRect().pos;
    shapes[i]->scale(factor);
    shapes[i]->move(scaledPosition(position, center, factor));
  }
}

void bykov::printShapes(std::ostream& output, const Shape* const* shapes, std::size_t count)
{
  double total = 0.0;
  for (std::size_t i = 0; i < count; ++i)
  {
    const double area = shapes[i]->getArea();
    const rectangle_t frame = shapes[i]->getFrameRect();
    total += area;
    output << area << " " << frame.width << " " << frame.height << " " << frame.pos.x << " " << frame.pos.y << "\n";
  }
  if (!std::isfinite(total))
  {
    throw std::overflow_error("Total area overflows");
  }
  const rectangle_t frame = getTotalFrame(shapes, count);
  output << total << "\n";
  output << frame.width << " " << frame.height << " " << frame.pos.x << " " << frame.pos.y << "\n";
}
