#include "diamond.h"

#include <stdexcept>

namespace kazbanov {

  Diamond::Diamond(double horizDiag, double vertDiag, const point_t& center):
    center_(center),
    horizDiag_(horizDiag),
    vertDiag_(vertDiag)
  {
    if (horizDiag <= 0.0 || vertDiag <= 0.0) {
      throw std::invalid_argument("horizDiag or vertDiag must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return horizDiag_ * vertDiag_ / 2.0;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return rectangle_t(horizDiag_, vertDiag_, center_);
  }

  void Diamond::move(const point_t& newPos)
  {
    center_ = newPos;
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
    horizDiag_ *= factor;
    vertDiag_ *= factor;
  }
} // namespace kazbanov
