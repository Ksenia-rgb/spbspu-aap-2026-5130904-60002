#include <iostream>

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

  void printShapesStats(fedorov::Shape** const shapes, const size_t size)
  {
    const double sum_area = fedorov::getShapesArea(shapes, size);
    const fedorov::rectangle_t rect = fedorov::getShapesFrameRect(shapes, size);
    std::cout << "Sum area = " << sum_area << ", shapes frame = Rectangle(width=" << rect.width
              << ", height=" << rect.height << ", pos=(" << rect.pos.x << ", " << rect.pos.y << "))\n";
  }
}

const size_t SHAPES_SIZE = 3;
const int POINTS_COUNT = 3;
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;

int main()
{
  fedorov::Shape* shapes[SHAPES_SIZE];

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
  std::cin >> new_x >> new_y >> factor;

  const fedorov::point_t rel_point = {new_x, new_y};

  for (size_t i = 0; i < SHAPES_SIZE; i++)
  {
    scaleRelative(shapes[i], rel_point, factor);
  }

  printShape(shapes[0], "Rectangle");
  printShape(shapes[1], "Ellipse");
  printShape(shapes[2], "Polygon");

  printShapesStats(shapes, SHAPES_SIZE);

  for (size_t i = 0; i < SHAPES_SIZE; i++)
  {
    delete shapes[i];
  }

  return 0;
}
