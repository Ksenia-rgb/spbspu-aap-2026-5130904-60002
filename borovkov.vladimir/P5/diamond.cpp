#include "diamond.hpp"

#include <stdexcept>

namespace borovkov
{
  Diamond::Diamond(double fg, double sd, const point_t& pos):
    first_diag_(fg),
    second_diag_(sd),
    center_(pos)
  {
    if (fg <= 0 || sd <= 0)
    {
      throw std::invalid_argument("Incorrect input. Both diagonals must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return first_diag_ * second_diag_ / 2;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {first_diag_, second_diag_, center_};
  }

  void Diamond::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }

  void Diamond::move(double x, double y)
  {
    center_.x += x;
    center_.y += y;
  }

  void Diamond::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Incorrect input. Factor must be positive");
    }
    first_diag_ *= factor;
    second_diag_ *= factor;
  }
}
