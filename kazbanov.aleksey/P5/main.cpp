#include "diamond.hpp"
#include "ellipse.hpp"
#include "rectangle.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

const int error = 1;

namespace kazbanov {
  rectangle_t getTotalFrameRect(Shape* const* shapes, size_t size)
  {
    rectangle_t first = shapes[0]->getFrameRect();
    double left = first.pos.x - first.width / 2.0;
    double right = first.pos.x + first.width / 2.0;
    double bottom = first.pos.y - first.height / 2.0;
    double top = first.pos.y + first.height / 2.0;
    for (size_t i = 1; i < size; i++) {
      rectangle_t r = shapes[i]->getFrameRect();
      left = std::min(left, r.pos.x - r.width / 2.0);
      right = std::max(right, r.pos.x + r.width / 2.0);
      bottom = std::min(bottom, r.pos.y - r.height / 2.0);
      top = std::max(top, r.pos.y + r.height / 2.0);
    }
    return {right - left, top - bottom, {(left + right) / 2.0, (bottom + top) / 2.0}};
  }

  void printFrame(const rectangle_t& r)
  {
    std::cout << "width = " << r.width << ", height = " << r.height << " center = (" << r.pos.x << ", " << r.pos.y << ")";
  }

  void printInfo(Shape* const* shapes, size_t size)
  {
    double total = 0;
    for (size_t i = 0; i < size; i++) {
      double area = shapes[i]->getArea();
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
    if (factor <= 0) {
      throw std::invalid_argument("factor must be greater than 0.");
    }
    for (size_t i = 0; i < size; i++) {
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
  Shape* shapes[size] = {};
  int code = 0;
  try {
    shapes[0] = new Rectangle{4, 2, {0, 0}};
    shapes[1] = new Rectangle{{-3, -1}, {-1, 2}};
    shapes[2] = new Diamond{6, 4, {5, 5}};
    shapes[3] = new Ellipse{3, 1.5, {-4, 6}};

    std::cout << "Before scaling:\n";
    printInfo(shapes, size);

    point_t pos{};
    double factor = 0.0;
    if (!(std::cin >> pos.x >> pos.y >> factor)) {
    std::cerr << "Error: invalid input\n";
    code = 1;
    } else {
      scaleShapes(shapes, pos, size, factor);
      std::cout << "After scaling:\n";
      printInfo(shapes, size);
    }
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    code = 1;
  }
  
  for(size_t i = 0; i < size; i++){
    delete shapes[i];
  }
  return code;
}
