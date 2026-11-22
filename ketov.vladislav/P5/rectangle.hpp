#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace ketov
{
class Rectangle : public Shape
{
public:
  Rectangle(rectangle_t rect);
  virtual ~Rectangle() = default;

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t new_pos) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  rectangle_t rect_;
};
} // namespace ketov

#endif
