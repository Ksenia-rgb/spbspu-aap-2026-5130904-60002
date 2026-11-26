#include "diamond.hpp"
#include "ellipse.hpp"
#include "rectangle.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

const double two = 2.0;
const double three = 3.0;
const double four = 4.0;

namespace kazbanov
{

  void deleteShapes(Shape** shapes, size_t count) noexcept
  {
    if (!shapes)
    {
      return;
    }
    for (size_t i = 0; i < count; i++)
    {
      delete shapes[i];
    }
    delete[] shapes;
  }

  rectangle_t getTotalFrameRect(Shape* const* shapes, size_t size)
  {
    const rectangle_t first = shapes[0]->getFrameRect();
    double left = first.pos.x - first.width / two;
    double right = first.pos.x + first.width / two;
    double bottom = first.pos.y - first.height / two;
    double top = first.pos.y + first.height / two;
    for (size_t i = 1; i < size; i++)
    {
      const rectangle_t r = shapes[i]->getFrameRect();
      left = std::min(left, r.pos.x - r.width / two);
      right = std::max(right, r.pos.x + r.width / two);
      bottom = std::min(bottom, r.pos.y - r.height / two);
      top = std::max(top, r.pos.y + r.height / two);
    }
    return {right - left, top - bottom, {(left + right) / two, (bottom + top) / two}};
  }

  void printFrame(const rectangle_t& r)
  {
    std::cout << "width = " << r.width << ", height = " << r.height << " center = (" << r.pos.x << ", " << r.pos.y
              << ")";
  }

  void printInfo(Shape* const* shapes, size_t size)
  {
    double total = 0;
    for (size_t i = 0; i < size; i++)
    {
      const double area = shapes[i]->getArea();
      total += area;
      std::cout << "Shape " << i + 1 << ": area = " << area << ", frame: ";
      printFrame(shapes[i]->getFrameRect());
      std::cout << "\n";
    }
    std::cout << "Total area: " << total << "\n";
    std::cout << "Total frame: ";
    printFrame(getTotalFrameRect(shapes, size));
    std::cout << "\n";
  }

  void scaleShapes(Shape* const* shape, const point_t& pos, size_t size, double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("factor must be greater than 0.");
    }
    for (size_t i = 0; i < size; i++)
    {
      const point_t center = shape[i]->getFrameRect().pos;
      shape[i]->move(pos);
      const point_t new_center = shape[i]->getFrameRect().pos;
      const double dx = center.x - new_center.x;
      const double dy = center.y - new_center.y;
      shape[i]->scale(factor);
      shape[i]->move(dx * factor, dy * factor);
    }
  }
}

int main()
{
  using namespace kazbanov;
  const size_t size = 4;
  Shape** shapes = nullptr;

  try
  {
    shapes = new Shape* [size]
    {
    };

    shapes[0] = new Rectangle{four, two, {0.0, 0.0}};
    shapes[1] = new Rectangle{{-three, -1.0}, {-1.0, two}};
    shapes[2] = new Diamond{two, four, {0.0, 0.0}};
    shapes[3] = new Ellipse{three, 1.0, {-four, 1.0}};

    std::cout << "Before scaling:\n";
    printInfo(shapes, size);

    point_t pos{};
    double factor = 0.0;
    if (!(std::cin >> pos.x >> pos.y >> factor))
    {
      std::cerr << "Error: invalid input\n";
      return 1;
    }
    else
    {
      scaleShapes(shapes, pos, size, factor);
      std::cout << "After scaling:\n";
      printInfo(shapes, size);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  deleteShapes(shapes, size);
  return 0;
}
