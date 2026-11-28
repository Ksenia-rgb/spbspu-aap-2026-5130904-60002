#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "rubber.hpp"
#include "shape.hpp"
#include "triangle.hpp"

namespace chenin
{
  void isoScale(Shape &shape, const point_t &anchor, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    const point_t b1 = shape.getFrameRect().pos;
    shape.move(anchor);
    const point_t b2 = shape.getFrameRect().pos;
    shape.scale(k);
    shape.move(k * (b1.x - b2.x), k * (b1.y - b2.y));
  }

  void isoScaleAll(Shape *const *shapes, std::size_t count, const point_t &anchor, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    for (std::size_t i = 0; i < count; ++i)
    {
      isoScale(*shapes[i], anchor, k);
    }
  }

  rectangle_t getTotalFrameRect(const Shape *const *shapes, std::size_t count)
  {
    const double MID_DIV = 2.0;
    const rectangle_t first = shapes[0]->getFrameRect();
    double min_x = first.pos.x - first.width / MID_DIV;
    double max_x = first.pos.x + first.width / MID_DIV;
    double min_y = first.pos.y - first.height / MID_DIV;
    double max_y = first.pos.y + first.height / MID_DIV;

    for (std::size_t i = 1; i < count; ++i)
    {
      const rectangle_t r = shapes[i]->getFrameRect();
      min_x = std::min(min_x, r.pos.x - r.width / MID_DIV);
      max_x = std::max(max_x, r.pos.x + r.width / MID_DIV);
      min_y = std::min(min_y, r.pos.y - r.height / MID_DIV);
      max_y = std::max(max_y, r.pos.y + r.height / MID_DIV);
    }

    const point_t center{(min_x + max_x) / MID_DIV, (min_y + max_y) / MID_DIV};
    return {max_x - min_x, max_y - min_y, center};
  }

  void printReport(const Shape *const *shapes, std::size_t count)
  {
    double total_area = 0.0;
    for (std::size_t i = 0; i < count; ++i)
    {
      const double area = shapes[i]->getArea();
      const rectangle_t frame = shapes[i]->getFrameRect();
      total_area += area;

      std::cout << "Shape #" << i << ": area=" << area;
      std::cout << ", frame=(w=" << frame.width << ", h=" << frame.height;
      std::cout << ", pos=(" << frame.pos.x << ", " << frame.pos.y << "))\n";
    }

    const rectangle_t total_frame = getTotalFrameRect(shapes, count);
    std::cout << "Total area=" << total_area << "\n";
    std::cout << "Total frame=(w=" << total_frame.width;
    std::cout << ", h=" << total_frame.height;
    std::cout << ", pos=(" << total_frame.pos.x;
    std::cout << ", " << total_frame.pos.y << "))\n";
  }

  void freeShapes(Shape **shapes, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
      shapes[i] = nullptr;
    }
  }
}

int main()
{
  const std::size_t COUNT = 3;
  chenin::Shape *shapes[COUNT] = {nullptr, nullptr, nullptr};

  const double RECT_W = 4.0;
  const double RECT_H = 2.0;
  const double TRI_X2 = 3.0;
  const double TRI_Y3 = 4.0;
  const double RUB_R_OUT = 5.0;

  try
  {
    shapes[0] = new chenin::Rectangle(RECT_W, RECT_H, {1.0, 1.0});
    shapes[1] = new chenin::Triangle({0.0, 0.0}, {TRI_X2, 0.0}, {0.0, TRI_Y3});
    shapes[2] = new chenin::Rubber({1.0, 0.0}, 1.0, {0.0, 0.0}, RUB_R_OUT);

    std::cout << "--- BEFORE ---\n";
    chenin::printReport(shapes, COUNT);

    chenin::point_t anchor{0.0, 0.0};
    double k = 1.0;
    if (!(std::cin >> anchor.x >> anchor.y >> k))
    {
      std::cerr << "Error: invalid input\n";
      chenin::freeShapes(shapes, COUNT);
      return 1;
    }

    chenin::isoScaleAll(shapes, COUNT, anchor, k);

    std::cout << "--- AFTER ---\n";
    chenin::printReport(shapes, COUNT);

    chenin::freeShapes(shapes, COUNT);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    chenin::freeShapes(shapes, COUNT);
    return 1;
  }

  return 0;
}
