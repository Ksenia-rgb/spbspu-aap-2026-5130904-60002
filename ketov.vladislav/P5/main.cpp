#include "base-types.hpp"
#include "complexquad.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
constexpr double two = 2.0;
constexpr double three = 3.0;
constexpr double four = 4.0;
constexpr size_t shapes_count = 3;

void scaleAtPoint(ketov::Shape *shape, ketov::point_t anchor, double factor) {
  if (factor <= 0.0) {
    throw std::invalid_argument("factor must be greater than zero");
  }

  const ketov::point_t f1 = shape->getFrameRect().pos;
  shape->move(anchor);
  shape->scale(factor);
  const ketov::point_t f2 = shape->getFrameRect().pos;

  const double dx = (anchor.x + (f1.x - anchor.x) * factor) - f2.x;
  const double dy = (anchor.y + (f1.y - anchor.y) * factor) - f2.y;
  shape->move(dx, dy);
}

ketov::rectangle_t getTotalFrameRect(
    const ketov::Shape *const *shapes, size_t count) {
  const ketov::rectangle_t first = shapes[0]->getFrameRect();
  double min_x = first.pos.x - first.width / two;
  double max_x = first.pos.x + first.width / two;
  double min_y = first.pos.y - first.height / two;
  double max_y = first.pos.y + first.height / two;

  for (size_t i = 1; i < count; ++i) {
    const ketov::rectangle_t frame = shapes[i]->getFrameRect();
    min_x = std::min(min_x, frame.pos.x - frame.width / two);
    max_x = std::max(max_x, frame.pos.x + frame.width / two);
    min_y = std::min(min_y, frame.pos.y - frame.height / two);
    max_y = std::max(max_y, frame.pos.y + frame.height / two);
  }

  return {max_x - min_x, max_y - min_y,
      {(min_x + max_x) / two, (min_y + max_y) / two}};
}

void printShapesInfo(const ketov::Shape *const *shapes, size_t count) {
  double total_area = 0.0;

  for (size_t i = 0; i < count; ++i) {
    const double area = shapes[i]->getArea();
    total_area += area;
    const ketov::rectangle_t frame = shapes[i]->getFrameRect();

    std::cout << "Shape #" << (i + 1) << ": area = " << area
              << ", frame = [width: " << frame.width
              << ", height: " << frame.height << ", center: (" << frame.pos.x
              << ", " << frame.pos.y << ")]\n";
  }

  const ketov::rectangle_t total_frame = getTotalFrameRect(shapes, count);
  std::cout << "Total area = " << total_area << "\n";
  std::cout << "Total frame = [width: " << total_frame.width
            << ", height: " << total_frame.height << ", center: ("
            << total_frame.pos.x << ", " << total_frame.pos.y << ")]\n";
}
}

int main() {
  try {
    ketov::Rectangle rect({four, two, {1.0, 1.0}});
    ketov::Triangle tri({0.0, 0.0}, {four, 0.0}, {0.0, three});
    ketov::Complexquad quad({0.0, four}, {four, 0.0}, {four, four}, {0.0, 0.0});

    ketov::Shape *shapes[shapes_count] = {&rect, &tri, &quad};

    std::cout << "--- Before scaling ---\n";
    printShapesInfo(shapes, shapes_count);

    std::cout << "\nEnter scale center (x y) and scale factor: ";
    ketov::point_t anchor{};
    double factor = 0.0;

    if (!(std::cin >> anchor.x >> anchor.y >> factor) || factor <= 0.0) {
      std::cerr << "Error: invalid scaling parameters\n";
      return 1;
    }

    for (size_t i = 0; i < shapes_count; ++i) {
      scaleAtPoint(shapes[i], anchor, factor);
    }

    std::cout << "\n--- After scaling ---\n";
    printShapesInfo(shapes, shapes_count);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
