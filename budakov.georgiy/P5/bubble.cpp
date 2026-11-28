#include <stdexcept>
#include "bubble.hpp"

namespace budakov
{
  const double PI = 3.1415;

  Bubble::Bubble(const double radius, const point_t& true_centre, const point_t& centre):
    radius_(radius),
    center_(centre),
    dx_(true_centre.x - centre.x),
    dy_(true_centre.y - centre.y)
  {
    if (radius_ <= 0)
    {
      throw std::invalid_argument("Wrong radius\n");
    }

    if (dx_ >= radius_ || dy_ >= radius_ || dx_ == 0.0 && dy_ == 0.0)
    {
      throw std::invalid_argument("Wrong centre point\n");
    }
  }

  double Bubble::getArea() const 
  {
    return PI * radius_ * radius_;
  }

  rectangle_t Bubble::getFrameRect() const
  {
    return {2 * radius_, 2 * radius_, {center_.x - dx_, center_.y - dy_} };
  }

  void Bubble::move(const point_t& target) noexcept
  {
    center_.x = target.x;
    center_.y = target.y;
  }

  void Bubble::move(const double mv_x, const double mv_y) noexcept
  {
    center_.x += mv_x;
    center_.y += mv_y;
  }

  void Bubble::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Wrong factor\n");
    }

    radius_ *= factor;
    dx_ *= factor;
    dy_ *= factor;
  }
}