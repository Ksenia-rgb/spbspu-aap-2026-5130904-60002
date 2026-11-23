#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "base-types.hpp"
#include "diamond.hpp"
#include "rectangle.hpp"
#include "ring.hpp"
#include "shape.hpp"

namespace borovkov
{
  rectangle_t getAllFrameRect(const Shape* const* shapes, size_t count)
  {
    if (!shapes || count == 0)
    {
      throw std::invalid_argument("Empty shapes array");
    }

    const double divisor = 2.0;

    rectangle_t rect = shapes[0]->getFrameRect();
    double min_x = rect.pos.x - rect.width / divisor;
    double max_x = rect.pos.x + rect.width / divisor;
    double min_y = rect.pos.y - rect.height / divisor;
    double max_y = rect.pos.y + rect.height / divisor;

    for (size_t i = 0; i < count; i++)
    {
      rect = shapes[i]->getFrameRect();
      const double left = rect.pos.x - rect.width / divisor;
      const double right = rect.pos.x + rect.width / divisor;
      const double bottom = rect.pos.y - rect.height / divisor;
      const double top = rect.pos.y + rect.height / divisor;

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
    return {max_x - min_x, max_y - min_y, {(min_x + max_x) / divisor, (min_y + max_y) / divisor}};
  }

  void printShapes(const Shape* const* shapes, size_t count)
  {
    if (!shapes || count == 0)
    {
      throw std::invalid_argument("Empty shapes array");
    }

    double result = 0.0;
    for (size_t i = 0; i < count; i++)
    {
      const rectangle_t rect = shapes[i]->getFrameRect();
      const double area = shapes[i]->getArea();
      std::cout << "Area: " << area << " ";
      std::cout << "Bounding rectangle: width = " << rect.width;
      std::cout << ", height = " << rect.height;
      std::cout << ", center = (" << rect.pos.x << ", ";
      std::cout << rect.pos.y << ")\n";

      result += area;
    }

    const rectangle_t all_rect = getAllFrameRect(shapes, count);
    std::cout << "All area: " << result << "\n";
    std::cout << "Bounding rectangle: width = " << all_rect.width;
    std::cout << ", height = " << all_rect.height;
    std::cout << ", center = (" << all_rect.pos.x;
    std::cout << ", " << all_rect.pos.y << ")\n";
  }

  void scaleShapes(Shape** shapes, size_t count, double factor, const point_t& scale_center)
  {
    if (!shapes || count == 0)
    {
      throw std::invalid_argument("Empty shapes array");
    }
    if (factor <= 0.0)
    {
      throw std::invalid_argument("Incorrect factor");
    }
    const double x0 = scale_center.x;
    const double y0 = scale_center.y;
    for (size_t i = 0; i < count; i++)
    {
      const double x = shapes[i]->getFrameRect().pos.x;
      const double y = shapes[i]->getFrameRect().pos.y;

      const double new_x = x0 + (x - x0) * factor;
      const double new_y = y0 + (y - y0) * factor;

      shapes[i]->move({new_x, new_y});
      shapes[i]->scale(factor);
    }
  }

  void deleteShapes(Shape** shapes, size_t count)
  {
    if (!shapes || count == 0)
    {
      return;
    }
    for (size_t i = 0; i < count; i++)
    {
      delete shapes[i];
      shapes[i] = nullptr;
    }
  }
}

int main()
{
  const size_t count = 4;
  borovkov::Shape* shapes[count]{};
  try
  {
    const double rect_w = 10.0;
    const double rect_h = 5.0;
    const borovkov::point_t rect_pos{0.0, 0.0};

    const double diag_x = 4.0;
    const double diag_y = 6.0;
    const borovkov::point_t diag_pos{2.0, 3.0};

    const double r_out = 5.0;
    const double r_in = 2.0;
    const borovkov::point_t ring_pos{-5.0, -5.0};

    const borovkov::point_t p1{5.0, 0.0};
    const borovkov::point_t p2{10.0, -5.0};

    shapes[0] = new borovkov::Rectangle(rect_w, rect_h, rect_pos);
    shapes[1] = new borovkov::Diamond(diag_x, diag_y, diag_pos);
    shapes[2] = new borovkov::Ring(r_out, r_in, ring_pos);
    shapes[3] = new borovkov::Rectangle(p1, p2);

    std::cout << "Before scaling:\n";
    borovkov::printShapes(shapes, count);

    double factor = 1.0;
    borovkov::point_t scale_center{0.0, 0.0};
    if (!(std::cin >> scale_center.x >> scale_center.y >> factor) || (factor <= 0.0))
    {
      throw std::invalid_argument("Incorrect input!!!");
    }
    std::cout << "\nScaling by factor " << factor << "\n\n";
    borovkov::scaleShapes(shapes, count, factor, scale_center);

    std::cout << "After scaling:\n";
    borovkov::printShapes(shapes, count);

    borovkov::deleteShapes(shapes, count);
  }
  catch (const std::exception& e)
  {
    borovkov::deleteShapes(shapes, count);
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
