#include <iostream>
#include <cstddef>

#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "polygon.hpp"
#include "geometry.hpp"

namespace fedorov
{
  void printShape(const fedorov::Shape* const shape, const char* const shape_name)
  {
    const fedorov::rectangle_t rect = shape->getFrameRect();
    std::cout << shape_name << "(area=" << shape->getArea() << ", frame=Rectangle(width=" << rect.width
              << ", height=" << rect.height << ", pos=(" << rect.pos.x << ", " << rect.pos.y << "))\n";
  }

  void printShapesStats(fedorov::Shape* const* const shapes, const std::size_t size)
  {
    const double sum_area = fedorov::getShapesArea(shapes, size);
    const fedorov::rectangle_t rect = fedorov::getShapesFrameRect(shapes, size);
    std::cout << "Sum area = " << sum_area << ", shapes frame = Rectangle(width=" << rect.width
              << ", height=" << rect.height << ", pos=(" << rect.pos.x << ", " << rect.pos.y << "))\n";
  }

  void deleteShapes(fedorov::Shape* const* shapes, const std::size_t size)
  {
    if (!shapes)
    {
      return;
    }
    for (std::size_t i = 0; i < size; i++)
    {
      delete shapes[i];
    }
    delete[] shapes;
    shapes = nullptr;
  }
}

const std::size_t SHAPES_SIZE = 3;
const int POINTS_COUNT = 3;

int main()
{
  fedorov::Shape** shapes = nullptr;
  try
  {
    shapes = new fedorov::Shape*[SHAPES_SIZE];

    shapes[0] = new fedorov::Rectangle({1, 2}, 3, 4);
    shapes[1] = new fedorov::Ellipse({0, 0}, 2, 4);

    fedorov::point_t poly_vertices[POINTS_COUNT] = {{0, 1}, {1, 4}, {3, 2}};
    shapes[2] = new fedorov::Polygon(poly_vertices, POINTS_COUNT);

    printShape(shapes[0], "Rectangle");
    printShape(shapes[1], "Ellipse");
    printShape(shapes[2], "Polygon");

    printShapesStats(shapes, SHAPES_SIZE);

    double new_x = 0;
    double new_y = 0;
    double factor = 0;
    if (!(std::cin >> new_x >> new_y >> factor) || factor <= 0)
    {
      deleteShapes(shapes, SHAPES_SIZE);

      std::cerr << "Invalid input for coordinates or scale factor\n";
      return 1;
    }

    const fedorov::point_t rel_point = {new_x, new_y};

    for (std::size_t i = 0; i < SHAPES_SIZE; i++)
    {
      scaleRelative(shapes[i], rel_point, factor);
    }

    printShape(shapes[0], "Rectangle");
    printShape(shapes[1], "Ellipse");
    printShape(shapes[2], "Polygon");

    printShapesStats(shapes, SHAPES_SIZE);
  }
  catch (const std::exception& exc)
  {
    deleteShapes(shapes, SHAPES_SIZE);
    std::cerr << exc.what() << "\n";
    return 2;
  }

  deleteShapes(shapes, SHAPES_SIZE);

  return 0;
}
