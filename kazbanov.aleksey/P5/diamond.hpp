#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include "shape.hpp"

namespace kazbanov
{
  class Diamond: public Shape
  {
  public:
    Diamond(double horiz_diag, double vert_diag, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double horiz_diag_;
    double vert_diag_;
    point_t center_;
  };
} // namespace kazbanov

#endif
