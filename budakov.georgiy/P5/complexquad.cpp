#include "complexquad.hpp"

namespace budakov
{
  const double eps = 1e-9;

  Complexquad::Complexquad(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& p4):
    p{ p1, p2, p3, p4 },
    center_{0.0, 0.0},
    crossed_type_(false)
  {
    bool cross1 = false;
    point_t potCenter1{};
    const double det1 = (p[1].x - p[0].x) * (p[3].y - p[2].y) - (p[1].y - p[0].y) * (p[3].x - p[2].x);
    if (std::abs(det1) >= eps)
    {
      const double t1 = ((p[2].x - p[0].x) * (p[3].y - p[2].y) - (p[2].y - p[0].y) * (p[3].x - p[2].x)) / det1;
      const double u1 = ((p[2].x - p[0].x) * (p[1].y - p[0].y) - (p[2].y - p[0].y) * (p[1].x - p[0].x)) / det1;
      if (t1 < 1 - eps && t1 > eps && u1 < 1 - eps && u1 > eps)
      {
        cross1 = true;
        potCenter1.x = p[0].x + t1 * (p[1].x - p[0].x);
        potCenter1.y = p[0].y + t1 * (p[1].y - p[0].y);
      }
    }

    bool cross2 = false;
    point_t potCenter2{};
    const double det2 = (p[2].x - p[1].x) * (p[0].y - p[3].y) - (p[2].y - p[1].y) * (p[0].x - p[3].x);
    if (std::abs(det2) >= eps)
    {
      const double t2 = ((p[3].x - p[1].x) * (p[0].y - p[3].y) - (p[3].y - p[1].y) * (p[0].x - p[3].x)) / det2;
      const double u2 = ((p[3].x - p[1].x) * (p[2].y - p[1].y) - (p[3].y - p[1].y) * (p[2].x - p[1].x)) / det2;
      if (t2 < 1 - eps && t2 > eps && u2 < 1 - eps && u2 > eps)
      {
        cross2 = true;
        potCenter2.x = p[1].x + t2 * (p[2].x - p[1].x);
        potCenter2.y = p[1].y + t2 * (p[2].y - p[1].y);
      }
    }

    if (cross1 == cross2)
    {
      throw std::invalid_argument("The shape is not a Complexquad\n");
    }

    if (cross1)
    {
      center_ = potCenter1;
    }
    else
    {
      center_ = potCenter2;
    }

    double area1 = 0.0;
    double area2 = 0.0;
    if (cross1)
    {
      area1 = 0.5 * std::abs((center_.x - p[0].x) * (p[3].y - p[0].y) - (p[3].x - p[0].x) * (center_.y - p[0].y));
      area2 = 0.5 * std::abs((p[2].x - p[1].x) * (center_.y - p[1].y) - (center_.x - p[1].x) * (p[2].y - p[1].y));
    }
    else
    {
      area1 = 0.5 * std::abs((p[1].x - p[0].x) * (center_.y - p[0].y) - (center_.x - p[0].x) * (p[1].y - p[0].y));
      area2 = 0.5 * std::abs((p[3].x - p[2].x) * (center_.y - p[2].y) - (center_.x - p[2].x) * (p[3].y - p[2].y));
    }

    if (area1 < eps || area2 < eps)
    {
      throw std::invalid_argument("Degenerate complexquad");
    }

    crossed_type_ = cross1;
  }

  double Complexquad::getArea() const
  {
    if (crossed_type_)
    {
      const double area1 = 0.5 * std::abs((center_.x - p[0].x) * (p[3].y - p[0].y) - (p[3].x - p[0].x) * (center_.y - p[0].y));
      const double area2 = 0.5 * std::abs((p[2].x - p[1].x) * (center_.y - p[1].y) - (center_.x - p[1].x) * (p[2].y - p[1].y));

      return area1 + area2;
    }
      const double area1 = 0.5 * std::abs((p[1].x - p[0].x) * (center_.y - p[0].y) - (center_.x - p[0].x) * (p[1].y - p[0].y));
      const double area2 = 0.5 * std::abs((p[3].x - p[2].x) * (center_.y - p[2].y) - (center_.x - p[2].x) * (p[3].y - p[2].y));

    return area1 + area2;
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    double min_x = p[0].x;
    double min_y = p[0].y;
    double max_x = p[0].x;
    double max_y = p[0].y;

    for (int i = 0; i < 4; i++)
    {
      if (p[i].x < min_x)
      {
        min_x = p[i].x;
      }
      if (p[i].x > max_x)
      {
        max_x = p[i].x;
      }
      if (p[i].y < min_y)
      {
        min_y = p[i].y;
      }
      if (p[i].y > max_y)
      {
        max_y = p[i].y;
      }
    }

    double width = max_x - min_x;
    double height = max_y - min_y;
    return { width, height, { min_x + (double)width/2, min_y + (double)height/2 } };

  }
  void Complexquad::move(const point_t& target) noexcept
  {
    double dx = target.x - center_.x;
    double dy = target.y - center_.y;

    center_ = target;
    for (int i = 0; i < 4; i++)
    {
      p[i].x += dx;
      p[i].y += dy;
    }

  }

  void Complexquad::move(const double mv_x, const double mv_y) noexcept
  {
    center_.x += mv_x;
    center_.y += mv_y;
    for (int i = 0; i < 4; i++)
    {
      p[i].x += mv_x;
      p[i].y += mv_y;
    }
  }

  void Complexquad::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Wrong factor\n");
    }
    for (int i = 0; i < 4; i++)
    {
      p[i].x = center_.x + (p[i].x - center_.x) * factor;
      p[i].y = center_.y + (p[i].y - center_.y) * factor;
    }
  }
}
