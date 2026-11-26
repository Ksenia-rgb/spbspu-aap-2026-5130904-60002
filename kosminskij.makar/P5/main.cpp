#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "base-types.hpp"
#include "diamond.hpp"
#include "rectangle.hpp"
#include "rubber.hpp"
#include "shape.hpp"

namespace kosminskij {
  namespace {
    constexpr std::size_t shapes_count = 3;

    void deleteShapes(Shape** shapes, std::size_t count) noexcept
    {
      if (!shapes) {
        return;
      }
      for (std::size_t i = 0; i < count; ++i) {
        delete shapes[i];
      }
      delete[] shapes;
    }

    void scaleAtPoint(Shape* shape, const point_t& anchor, double factor)
    {
      if (factor <= 0.0) {
        throw std::invalid_argument("scale factor must be greater than zero");
      }

      const point_t f1 = shape->getFrameRect().pos;
      shape->move(anchor);
      shape->scale(factor);
      const point_t f2 = shape->getFrameRect().pos;

      const double dx = (anchor.x + (f1.x - anchor.x) * factor) - f2.x;
      const double dy = (anchor.y + (f1.y - anchor.y) * factor) - f2.y;
      shape->move(dx, dy);
    }

    rectangle_t getTotalFrameRect(const Shape* const* shapes, std::size_t count)
    {
      const rectangle_t first = shapes[0]->getFrameRect();
      double min_x = first.pos.x - first.width / 2.0;
      double max_x = first.pos.x + first.width / 2.0;
      double min_y = first.pos.y - first.height / 2.0;
      double max_y = first.pos.y + first.height / 2.0;

      for (std::size_t i = 1; i < count; ++i) {
        const rectangle_t frame = shapes[i]->getFrameRect();
        min_x = std::min(min_x, frame.pos.x - frame.width / 2.0);
        max_x = std::max(max_x, frame.pos.x + frame.width / 2.0);
        min_y = std::min(min_y, frame.pos.y - frame.height / 2.0);
        max_y = std::max(max_y, frame.pos.y + frame.height / 2.0);
      }

      return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
    }

    void printFrame(const rectangle_t& frame)
    {
      std::cout << "[width: " << frame.width << ", height: " << frame.height << ", center: ("
                << frame.pos.x << ", " << frame.pos.y << ")]";
    }

    void printShapesInfo(const Shape* const* shapes, std::size_t count)
    {
      double total_area = 0.0;
      for (std::size_t i = 0; i < count; ++i) {
        const double area = shapes[i]->getArea();
        total_area += area;
        std::cout << "Shape #" << (i + 1) << ": area = " << area << ", frame = ";
        printFrame(shapes[i]->getFrameRect());
        std::cout << "\n";
      }
      std::cout << "Total area = " << total_area << "\n";
      std::cout << "Total frame = ";
      printFrame(getTotalFrameRect(shapes, count));
      std::cout << "\n";
    }
  }
}

int main()
{
  kosminskij::Shape** shapes = nullptr;
  try {
    shapes = new kosminskij::Shape* [kosminskij::shapes_count]
    {
    };

    shapes[0] = new kosminskij::Rectangle({1.0, 2.0}, 4.0, 3.0);
    shapes[1] = new kosminskij::Diamond({-3.0, 0.0}, 6.0, 4.0);
    shapes[2] = new kosminskij::Rubber({5.0, 5.0}, 1.0, {5.5, 5.0}, 3.0);

    std::cout << "--- Before scaling ---\n";
    kosminskij::printShapesInfo(shapes, kosminskij::shapes_count);

    std::cout << "\nEnter scale center (x y) and scale factor: ";
    kosminskij::point_t anchor{};
    double factor = 0.0;
    if (!(std::cin >> anchor.x >> anchor.y >> factor)) {
      std::cerr << "Error: invalid scaling parameters\n";
      kosminskij::deleteShapes(shapes, kosminskij::shapes_count);
      return 1;
    }

    for (std::size_t i = 0; i < kosminskij::shapes_count; ++i) {
      kosminskij::scaleAtPoint(shapes[i], anchor, factor);
    }

    std::cout << "\n--- After scaling ---\n";
    kosminskij::printShapesInfo(shapes, kosminskij::shapes_count);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    kosminskij::deleteShapes(shapes, kosminskij::shapes_count);
    return 1;
  }

  kosminskij::deleteShapes(shapes, kosminskij::shapes_count);
  return 0;
}
