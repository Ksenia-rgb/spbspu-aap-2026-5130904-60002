#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace chenin
{
  Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):
    a_(a),
    b_(b),
    c_(c)
  {
    const double EPS = 1e-12;
    if (getArea() <= EPS)
    {
      throw std::invalid_argument("Triangle vertices must not be collinear");
    }
  }

  point_t Triangle::getCenter() const
  {
    const double CENTROID_DIV = 3.0;
    const double cx = (a_.x + b_.x + c_.x) / CENTROID_DIV;
    const double cy = (a_.y + b_.y + c_.y) / CENTROID_DIV;
    return {cx, cy};
  }

  double Triangle::getArea() const
  {
    const double HALF = 0.5;
    const double det = (b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y);
    return HALF * std::abs(det);
  }

  rectangle_t Triangle::getFrameRect() const
  {
    const double min_x = std::min(a_.x, std::min(b_.x, c_.x));
    const double max_x = std::max(a_.x, std::max(b_.x, c_.x));
    const double min_y = std::min(a_.y, std::min(b_.y, c_.y));
    const double max_y = std::max(a_.y, std::max(b_.y, c_.y));
    const double MID_DIV = 2.0;
    const point_t center{(min_x + max_x) / MID_DIV, (min_y + max_y) / MID_DIV};
    return {max_x - min_x, max_y - min_y, center};
  }

  void Triangle::move(double dx, double dy)
  {
    a_.x += dx;
    a_.y += dy;
    b_.x += dx;
    b_.y += dy;
    c_.x += dx;
    c_.y += dy;
  }

  void Triangle::move(const point_t &pos)
  {
    const point_t center = getCenter();
    move(pos.x - center.x, pos.y - center.y);
  }

  void Triangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    const point_t center = getCenter();
    a_.x = center.x + (a_.x - center.x) * k;
    a_.y = center.y + (a_.y - center.y) * k;
    b_.x = center.x + (b_.x - center.x) * k;
    b_.y = center.y + (b_.y - center.y) * k;
    c_.x = center.x + (c_.x - center.x) * k;
    c_.y = center.y + (c_.y - center.y) * k;
  }
}
