#include <iostream>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include "diamond.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

namespace udovichenko
{
  constexpr std::size_t MAX_SHAPES = 10;

  void printShapes(const IShape *const shapes[], std::size_t max_count)
  {
    if (!shapes)
    {
      return;
    }
    double total_area = 0.0;
    double max_x = std::numeric_limits< double >::lowest();
    double min_x = std::numeric_limits< double >::max();
    double max_y = std::numeric_limits< double >::lowest();
    double min_y = std::numeric_limits< double >::max();
    for (std::size_t i = 0; i < max_count; i++)
    {
      const IShape *const shape = shapes[i];
      if (!shape)
      {
        continue;
      }

      const double area = shape->getArea();
      const rectangle_t frame = shape->getFrameRect();

      std::cout << "Area of " << shape << ": " << area << '\n';
      std::cout << "Frame rectangle of " << shape;
      std::cout << ": w=" << frame.width << " h=" << frame.height;
      std::cout << " center=(" << frame.center.x << ", " << frame.center.y << ")\n\n";

      total_area += area;
      max_x = std::max(max_x, frame.center.x + frame.width / 2);
      min_x = std::min(min_x, frame.center.x - frame.width / 2);
      max_y = std::max(max_y, frame.center.y + frame.height / 2);
      min_y = std::min(min_y, frame.center.y - frame.height / 2);
    }

    std::cout << "Total area: " << total_area << '\n';
    std::cout << "Frame rectangle: " << "w=" << max_x - min_x << " h=" << max_y - min_y;
    std::cout << " center=(" << (max_x + min_x) / 2 << ", " << (max_y + min_y) / 2 << ")\n\n";
  }

  void scaleShapes(IShape *const shapes[], std::size_t max_count, const point_t &center, double factor)
  {
    if (!shapes)
    {
      return;
    }
    for (std::size_t i = 0; i < max_count; i++)
    {
      IShape *const shape = shapes[i];
      if (!shape)
      {
        continue;
      }
      const point_t prev_frame_center = shape->getFrameRect().center;
      shape->move(center);
      const point_t new_frame_center = shape->getFrameRect().center;
      const double dx = new_frame_center.x - prev_frame_center.x;
      const double dy = new_frame_center.y - prev_frame_center.y;
      shape->scale(factor);
      shape->move(-dx * factor, -dy * factor);
    }
  }
}

int main()
{
  udovichenko::IShape *shapes[udovichenko::MAX_SHAPES]{};
  try
  {
    shapes[0] = new udovichenko::Rectangle{2, 2, {1, 0}};
    shapes[1] = new udovichenko::Diamond{3, 1, {4, 4}};
    shapes[2] = new udovichenko::Triangle{{0, 4}, {4, 0}, {0, 2}};
    shapes[3] = new udovichenko::Rectangle{{1, 1}, {3, 3}};
    udovichenko::printShapes(shapes, udovichenko::MAX_SHAPES);

    double scale_factor = 1.0;
    udovichenko::point_t scale_center;
    if (!(std::cin >> scale_center.x >> scale_center.y >> scale_factor) || scale_factor <= 0.0)
    {
      throw std::runtime_error("Invalid input for scale point (x, y) or scale factor");
    }
    udovichenko::scaleShapes(shapes, udovichenko::MAX_SHAPES, scale_center, scale_factor);
    udovichenko::printShapes(shapes, udovichenko::MAX_SHAPES);
  }
  catch (const std::exception &e)
  {
    for (auto &shape : shapes)
    {
      delete shape;
      shape = nullptr;
    }
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  for (auto &shape : shapes)
  {
    delete shape;
    shape = nullptr;
  }

  return 0;
}
