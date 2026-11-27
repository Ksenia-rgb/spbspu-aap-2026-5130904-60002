#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace borovkov
{
  class Diamond: public Shape
  {
  public:
    Diamond(double fd, double sd, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double x, double y) override;
    void scale(double factor) override;

  private:
    double first_diag_;
    double second_diag_;
    point_t center_;
  };
}

#endif
