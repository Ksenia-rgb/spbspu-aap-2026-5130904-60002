#include "diamond.hpp"

#include <stdexcept>

namespace kosminskij
{
  namespace
  {
    constexpr double two = 2.0;
  }

  Diamond::Diamond(const point_t& center, double hor_diagonal, double ver_diagonal):
    center_(center),
    hor_diagonal_(hor_diagonal),
    ver_diagonal_(ver_diagonal)
  {
    if (hor_diagonal <= 0.0 || ver_diagonal <= 0.0)
    {
      throw std::invalid_argument("Diamond: diagonals must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return hor_diagonal_ * ver_diagonal_ / two;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {hor_diagonal_, ver_diagonal_, center_};
  }

  void Diamond::move(const point_t& p)
  {
    center_ = p;
  }

  void Diamond::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Diamond::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Diamond: scale factor must be positive");
    }
    hor_diagonal_ *= k;
    ver_diagonal_ *= k;
  }
}
