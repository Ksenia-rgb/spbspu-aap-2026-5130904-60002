#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>

#include "shape.hpp"
#include "base-types.hpp"

namespace fedorov
{
  class Polygon: public Shape
  {
  public:
    Polygon(point_t* vertices, size_t size);
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    Polygon& operator=(Polygon&& other) noexcept;
    ~Polygon();

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_pos) override;
    void move(double delta_x, double delta_y) override;
    void scale(double factor) override;
  private:
    size_t vertices_count_;
    point_t* vertices_;
    point_t center_;
  };
}

#endif
