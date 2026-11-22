#include <iostream>
#include <stdexcept>

#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "xquare.hpp"
#include "rubber.hpp"

namespace oglov
{
  constexpr double half = 0.5;
  constexpr size_t shape_count = 3;

  void printFrameRect(const rectangle_t& r)
  {
    std::cout << "width = " << r.width << ", height = " << r.height << ", position = { " << r.pos.x << ", " << r.pos.y
              << " }\n";
  }

  rectangle_t commonFrameRect(Shape* const* shapes)
  {
    rectangle_t init = shapes[0]->getFrameRect();
    double min_x = init.pos.x - init.width * half;
    double max_x = init.pos.x + init.width * half;
    double min_y = init.pos.y - init.height * half;
    double max_y = init.pos.y + init.height * half;

    for (size_t i = 1; i < shape_count; ++i)
    {
      init = shapes[i]->getFrameRect();
      const double left = init.pos.x - init.width * half;
      const double right = init.pos.x + init.width * half;
      const double bottom = init.pos.y - init.height * half;
      const double top = init.pos.y + init.height * half;

      if (left < min_x)
      {
        min_x = left;
      }
      if (right > max_x)
      {
        max_x = right;
      }
      if (bottom < min_y)
      {
        min_y = bottom;
      }
      if (top > max_y)
      {
        max_y = top;
      }
    }

    return rectangle_t{max_x - min_x, max_y - min_y, {(max_x + min_x) * half, (max_y + min_y) * half}};
  }

  void printShape(Shape* const* shapes)
  {
    std::cout << "Rectangle: \n";
    std::cout << "Area = " << shapes[0]->getArea() << "\nRectangle frame Rectangle: ";
    printFrameRect(shapes[0]->getFrameRect());

    std::cout << "Xquare: \n";
    std::cout << "Area = " << shapes[1]->getArea() << "\nXquare frame Rectangle: ";
    printFrameRect(shapes[1]->getFrameRect());

    std::cout << "Rubber: \n";
    std::cout << "Area = " << shapes[2]->getArea() << "\nRubber frame Rectangle: ";
    printFrameRect(shapes[2]->getFrameRect());

    double sum_area = 0.0;
    for (size_t i = 0; i < shape_count; ++i)
    {
      sum_area += shapes[i]->getArea();
    }

    std::cout << "\n\nSumArea = " << sum_area << ", common frame rectangle: ";
    printFrameRect(commonFrameRect(shapes));
  }

  void scaleAll(Shape* const* shapes, const point_t& center, double k)
  {
    for (size_t i = 0; i < shape_count; ++i)
    {
      const rectangle_t fr = shapes[i]->getFrameRect();
      const double dx = fr.pos.x - center.x;
      const double dy = fr.pos.y - center.y;

      shapes[i]->scale(k);
      shapes[i]->move(point_t{center.x + dx * k, center.y + dy * k});
    }
  }
}

int main()
{
  Shape* shapes[oglov::shape_count] = {nullptr, nullptr, nullptr};

  constexpr double rect_w = 3.0;
  constexpr double rect_h = 4.0;
  constexpr point_t rect_pos{1.0, 1.0};

  constexpr double xq_d = 7.0;
  constexpr point_t xq_pos{2.0, 2.0};

  constexpr double rb_r_big = 5.0;
  constexpr point_t rb_pos_big{-1.0, -1.0};
  constexpr double rb_r_small = 2.0;
  constexpr point_t rb_pos_small{0.0, 0.0};

  int ret = 0;
  try
  {
    shapes[0] = new Rectangle(rect_w, rect_h, rect_pos);
    shapes[1] = new Xquare(xq_d, xq_pos);
    shapes[2] = new Rubber(rb_r_big, rb_pos_big, rb_r_small, rb_pos_small);

    oglov::printShape(shapes);

    double x = 0.0;
    double y = 0.0;
    double k = 0.0;
    if (!(std::cin >> x >> y >> k))
    {
      throw std::runtime_error("Invalid input");
    }

    oglov::scaleAll(shapes, point_t{x, y}, k);

    oglov::printShape(shapes);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    ret = 1;
  }

  for (size_t i = 0; i < oglov::shape_count; ++i)
  {
    delete shapes[i];
  }

  return ret;
}
