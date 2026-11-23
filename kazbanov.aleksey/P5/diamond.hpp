#ifndef P5_DIAMOND_H
#define P5_DIAMOND_H
#include "shape.h"

namespace kazbanov {
  class Diamond: public Shape {
  public:
    Diamond(double horizDiag, double vertDiag, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double horizDiag_;
    double vertDiag_;
    point_t center_;
  };
} // namespace kazbanov

#endif
