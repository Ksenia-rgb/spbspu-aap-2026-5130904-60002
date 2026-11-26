#include "diamond.hpp"

#include <stdexcept>

namespace kosminskij {
  Diamond::Diamond(const point_t& center, double horDiagonal, double verDiagonal):
    center_(center),
    horDiagonal_(horDiagonal),
    verDiagonal_(verDiagonal)
  {
    if (horDiagonal <= 0.0 || verDiagonal <= 0.0) {
      throw std::invalid_argument("Diamond: diagonals must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return horDiagonal_ * verDiagonal_ / 2.0;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {horDiagonal_, verDiagonal_, center_};
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
    if (k <= 0.0) {
      throw std::invalid_argument("Diamond: scale factor must be positive");
    }
    horDiagonal_ *= k;
    verDiagonal_ *= k;
  }
}
