#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "complexquad.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"

void scaleAtPoint(ketov::Shape *shape, ketov::point_t anchor, double factor)
{
  if (factor <= 0.0) {
    throw std::invalid_argument("factor must be greater than zero");
  }

  ketov::point_t f1 = shape->getFrameRect().pos;
  shape->move(anchor);
  shape->scale(factor);
  ketov::point_t f2 = shape->getFrameRect().pos;

  double dx = (anchor.x + (f1.x - anchor.x) * factor) - f2.x;
  double dy = (anchor.y + (f1.y - anchor.y) * factor) - f2.y;
  shape->move(dx, dy);
}

ketov::rectangle_t getTotalFrameRect(const ketov::Shape *const *shapes, size_t count)
{
  ketov::rectangle_t first = shapes[0]->getFrameRect();
  double min_x = first.pos.x - first.width / 2.0;
  double max_x = first.pos.x + first.width / 2.0;
  double min_y = first.pos.y - first.height / 2.0;
  double max_y = first.pos.y + first.height / 2.0;

  for (size_t i = 1; i < count; i++) {
    ketov::rectangle_t frame = shapes[i]->getFrameRect();
    min_x = std::min(min_x, frame.pos.x - frame.width / 2.0);
    max_x = std::max(max_x, frame.pos.x + frame.width / 2.0);
    min_y = std::min(min_y, frame.pos.y - frame.height / 2.0);
    max_y = std::max(max_y, frame.pos.y + frame.height / 2.0);
  }

  return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
}

void printShapesInfo(const ketov::Shape *const *shapes, size_t count)
{
  double total_area = 0.0;

  for (size_t i = 0; i < count; ++i) {
    double area = shapes[i]->getArea();
    total_area += area;
    ketov::rectangle_t frame = shapes[i]->getFrameRect();

    std::cout << "Shape #" << (i + 1) << ": area = " << area << ", frame = [width: " << frame.width
              << ", height: " << frame.height << ", center: (" << frame.pos.x << ", " << frame.pos.y << ")]\n";
  }

  ketov::rectangle_t total_frame = getTotalFrameRect(shapes, count);
  std::cout << "Total area = " << total_area << "\n";
  std::cout << "Total frame = [width: " << total_frame.width << ", height: " << total_frame.height << ", center: ("
            << total_frame.pos.x << ", " << total_frame.pos.y << ")]\n";
}

int main()
{
  try {
    ketov::Rectangle rect({4.0, 2.0, {1.0, 1.0}});
    ketov::Triangle tri({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0});
    ketov::Complexquad quad({0.0, 4.0}, {4.0, 0.0}, {4.0, 4.0}, {0.0, 0.0});

    const size_t shapes_count = 3;
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
