#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace bykov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(point_t center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t position) override;
    void move(double dx, double dy) override;

  protected:
    void scaleUnsafely(double factor) override;

  private:
    rectangle_t frame_;
  };
}

#endif
