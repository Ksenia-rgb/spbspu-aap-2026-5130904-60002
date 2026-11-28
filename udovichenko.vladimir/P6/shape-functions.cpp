#include "shape-functions.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include "../common/shape.hpp"

namespace udovichenko
{
  void printShapes(const CompositeShape &shapes)
  {
    if (shapes.empty())
    {
      std::cout << "Shapes are empty to print their information\n";
      return;
    }

    double total_area = 0.0;
    double max_x = std::numeric_limits< double >::lowest();
    double min_x = std::numeric_limits< double >::max();
    double max_y = std::numeric_limits< double >::lowest();
    double min_y = std::numeric_limits< double >::max();
    for (std::size_t i = 0; i < shapes.size(); i++)
    {
      const IShape &shape = shapes.get(i);
      const rectangle_t frame = shape.getFrameRect();
      std::cout << "Shape " << i << ":\n";
      std::cout << "Area: " << shape.getArea() << '\n';
      std::cout << "Frame rectangle: w=" << frame.width << " h=" << frame.height;
      std::cout << " center=(" << frame.center.x << ", " << frame.center.y << ")\n\n";

      total_area += shape.getArea();
      max_x = std::max(max_x, frame.center.x + frame.width / 2);
      max_y = std::max(max_y, frame.center.y + frame.height / 2);
      min_x = std::min(min_x, frame.center.x - frame.width / 2);
      min_y = std::min(min_y, frame.center.y - frame.height / 2);
    }

    std::cout << "Total area: " << total_area << '\n';
    std::cout << "Total frame rectangle: w=" << max_x - min_x << " h=" << max_y - min_y;
    std::cout << " center=(" << (min_x + max_x) / 2 << ", " << (min_y + max_y) / 2 << ")\n\n";
  }

  void allotropicScaleShapes(CompositeShape &shapes, const point_t &point, double factor)
  {
    for (std::size_t i = 0; i < shapes.size(); i++)
    {
      IShape &shape = shapes.get(i);
      const point_t prev_frame_center = shape.getFrameRect().center;
      shape.move(point);
      const point_t new_frame_center = shape.getFrameRect().center;
      const double dx = new_frame_center.x - prev_frame_center.x;
      const double dy = new_frame_center.y - prev_frame_center.y;
      shape.scale(factor);
      shape.move(-dx * factor, -dy * factor);
    }
  }
}
