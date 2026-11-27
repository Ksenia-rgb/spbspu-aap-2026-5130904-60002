#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace zelpus
{

  class Diamond final: public Shape
  {
  public:
    Diamond(const point_t & center, double horizDiag, double vertDiag);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    point_t center_;
    double horiz_;
    double vert_;
  };
}

#endif
