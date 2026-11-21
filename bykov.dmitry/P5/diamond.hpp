#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace bykov
{
  class Diamond: public Shape
  {
  public:
    Diamond(point_t center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t position) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    rectangle_t frame_;
  };
}

#endif
