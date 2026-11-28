#include "rubber.hpp"
#include <cmath>
#include <stdexcept>

namespace chenin
{
  Rubber::Rubber(const point_t &in_pos, double in_r, const point_t &out_pos, double out_r):
    inner_center_(in_pos),
    inner_radius_(in_r),
    outer_center_(out_pos),
    outer_radius_(out_r)
  {
    if (inner_radius_ <= 0.0 || outer_radius_ <= 0.0)
    {
      throw std::invalid_argument("Rubber radii must be positive");
    }
    const double dx = outer_center_.x - inner_center_.x;
    const double dy = outer_center_.y - inner_center_.y;
    const double dist = std::sqrt(dx * dx + dy * dy);
    const double EPS = 1e-12;

    if (dist <= EPS)
    {
      throw std::invalid_argument("Rubber circles must not be concentric");
    }
    if (dist + inner_radius_ >= outer_radius_)
    {
      throw std::invalid_argument("Inner circle must lie inside outer circle");
    }
  }

  double Rubber::getArea() const
  {
    const double PI = std::acos(-1.0);
    const double diff = outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_;
    return PI * diff;
  }

  rectangle_t Rubber::getFrameRect() const
  {
    const double DIAMETER_MULT = 2.0;
    const double side = DIAMETER_MULT * outer_radius_;
    return {side, side, outer_center_};
  }

  void Rubber::move(double dx, double dy)
  {
    inner_center_.x += dx;
    inner_center_.y += dy;
    outer_center_.x += dx;
    outer_center_.y += dy;
  }

  void Rubber::move(const point_t &pos)
  {
    move(pos.x - inner_center_.x, pos.y - inner_center_.y);
  }

  void Rubber::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    inner_radius_ *= k;
    outer_radius_ *= k;
    outer_center_.x = inner_center_.x + (outer_center_.x - inner_center_.x) * k;
    outer_center_.y = inner_center_.y + (outer_center_.y - inner_center_.y) * k;
  }
}
