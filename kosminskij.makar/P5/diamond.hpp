#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace kosminskij
{
  // Ромб с диагоналями, параллельными осям координат
  class Diamond: public Shape
  {
  public:
    Diamond(const point_t& center, double hor_diagonal, double ver_diagonal);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t center_;
    double hor_diagonal_;
    double ver_diagonal_;
  };
}

#endif
