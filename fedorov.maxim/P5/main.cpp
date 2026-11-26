#include <iostream>

#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "polygon.hpp"
#include "geometry.hpp"

void printShape(fedorov::Shape* shape, const char* shape_name)
{
  fedorov::rectangle_t rect = shape->getFrameRect();
  std::cout << shape_name << "(area=" << shape->getArea() << ", frame=Rectangle(width=" << rect.width
            << ", height=" << rect.height << ", pos=(" << rect.pos.x << ", " << rect.pos.y << "))\n";
}

void printShapesStats(fedorov::Shape** shapes, const size_t size)
{
  double sum_area = fedorov::getShapesArea(shapes, size);
  fedorov::rectangle_t rect = fedorov::getShapesFrameRect(shapes, size);
  std::cout << "Sum area = " << sum_area << ", shapes frame = Rectangle(width=" << rect.width
            << ", height=" << rect.height << ", pos=(" << rect.pos.x << ", " << rect.pos.y << "))\n";
}

const size_t SHAPES_SIZE = 3;
const int pointsCOUNT = 3;

int main()
{
  fedorov::Shape* shapes[SHAPES_SIZE];

  shapes[0] = new fedorov::Rectangle({1, 2}, 3, 4);
  shapes[1] = new fedorov::Ellipse({0, 0}, 2, 4);

  fedorov::point_t poly_vertices[pointsCOUNT] = {{0, 1}, {1, 4}, {3, 2}};
  shapes[2] = new fedorov::Polygon(poly_vertices, pointsCOUNT);

  printShape(shapes[0], "Rectangle");
  printShape(shapes[1], "Ellipse");
  printShape(shapes[2], "Polygon");

  printShapesStats(shapes, SHAPES_SIZE);

  double new_x, new_y, factor;
  std::cin >> new_x >> new_y >> factor;

  fedorov::point_t rel_point = {new_x, new_y};

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
