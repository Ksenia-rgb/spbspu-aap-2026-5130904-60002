#include "rubber.hpp"

#include <cmath>
#include <stdexcept>

namespace kosminskij
{
  namespace
  {
    constexpr double kPi = 3.14159265358979323846;
    constexpr double two = 2.0;
  }

  Rubber::Rubber(const point_t& center, double inner_radius, const point_t& outer_center, double outer_radius):
    center_(center),
    outer_center_(outer_center),
    inner_radius_(inner_radius),
    outer_radius_(outer_radius)
  {
    if (inner_radius <= 0.0 || outer_radius <= inner_radius)
    {
      throw std::invalid_argument("Rubber: need 0 < inner radius < outer radius");
    }
    const double dist = std::hypot(outer_center.x - center.x, outer_center.y - center.y);
    if (dist == 0.0)
    {
      throw std::invalid_argument("Rubber: circles must not be concentric");
    }
    if (dist + inner_radius >= outer_radius)
    {
      throw std::invalid_argument("Rubber: inner circle must lie strictly inside the outer one");
    }
  }

  double Rubber::getArea() const
  {
    return kPi * (outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_);
  }

  rectangle_t Rubber::getFrameRect() const
  {
    return {two * outer_radius_, two * outer_radius_, outer_center_};
  }

  void Rubber::move(const point_t& p)
  {
    move(p.x - center_.x, p.y - center_.y);
  }

  void Rubber::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
    outer_center_.x += dx;
    outer_center_.y += dy;
  }

  void Rubber::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Rubber: scale factor must be positive");
    }
    inner_radius_ *= k;
    outer_radius_ *= k;
    outer_center_.x = center_.x + (outer_center_.x - center_.x) * k;
    outer_center_.y = center_.y + (outer_center_.y - center_.y) * k;
  }
}
