#include "diamond.hpp"
#include <stdexcept>

namespace kazbanov {
  Diamond::Diamond(double horiz_diag, double vert_diag, const point_t& center):
    horizDiag_(horiz_diag),
    vertDiag_(vert_diag),
    center_(center)
  {
    if (horiz_diag <= 0.0 || vert_diag <= 0.0) {
      throw std::invalid_argument("horizDiag or vertDiag must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return horiz_diag_ * vert_diag_ / 2.0;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return rectangle_t{horiz_diag_, vert_diag_, center_};
  }

  void Diamond::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Diamond::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Diamond::scale(double factor)
  {
    if (factor <= 0.0) {
      throw std::invalid_argument("factor must be positive");
    }
    horiz_diag_ *= factor;
    vert_diag_ *= factor;
  }
}
