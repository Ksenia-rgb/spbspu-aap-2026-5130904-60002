#include "rectangle.hpp"
#include "ring.hpp"
#include "concave.hpp"

#include <iostream>
#include <algorithm>

namespace
{
  const int INPUT_ERROR = 1;
  const int ALLOCATION_ERROR = 2;

  const std::size_t SIZE = 3;

  const double RECTANGLE_WIDTH = 4;
  const double RECTANGLE_HEIGHT = 6;
  const korotkin::point_t RECTANGLE_CENTER = {0, 0};

  const double RING_OUTER_RADIUS = 5;
  const double RING_INNER_RADIUS = 2;
  const korotkin::point_t RING_CENTER = {7, 3};

  const korotkin::point_t CONCAVE_A = {0, 0};
  const korotkin::point_t CONCAVE_B = {4, 0};
  const korotkin::point_t CONCAVE_C = {2, 1};
  const korotkin::point_t CONCAVE_D = {4, 4};
}

namespace korotkin
{
  void deleteShapes(const Shape * const * const shapes)
  {
    if(shapes)
    {
      for(std::size_t i = 0; i < SIZE; i++)
      {
        delete shapes[i];
      }
    }
  }

  double getTotalArea(const Shape * const * const shapes)
  {
    double sum = 0;

    for(std::size_t i = 0; i < SIZE; i++)
    {
      sum += shapes[i]->getArea();
    }

    return sum;
  }

  rectangle_t getTotalFrameRect(const Shape * const * const shapes)
  {
    const rectangle_t first = shapes[0]->getFrameRect();
    double minX = first.pos.x - (first.width / 2);
    double maxX = first.pos.x + (first.width / 2);
    double minY = first.pos.y - (first.height / 2);
    double maxY = first.pos.y + (first.height / 2);

    for(std::size_t i = 1; i < SIZE; i++)
    {
      const rectangle_t curr = shapes[i]->getFrameRect();
      const double currMinX = curr.pos.x - curr.width / 2;
      const double currMaxX = curr.pos.x + curr.width / 2;
      const double currMinY = curr.pos.y - curr.height / 2;
      const double currMaxY = curr.pos.y + curr.height / 2;

      minX = std::min(minX, currMinX);
      maxX = std::max(maxX, currMaxX);
      minY = std::min(minY, currMinY);
      maxY = std::max(maxY, currMaxY);
    }

    const double width = maxX - minX;
    const double height = maxY - minY;
    const point_t center{(minX + maxX) / 2, (minY + maxY) / 2};

    return rectangle_t{width, height, center};
  }

  void scaleAroundPoint(Shape * const * const shapes, point_t point, double factor)
  {
    for (std::size_t i = 0; i < SIZE; i++)
    {
      const point_t before = shapes[i]->getFrameRect().pos;
      shapes[i]->move(point);
      const point_t after = shapes[i]->getFrameRect().pos;

      shapes[i]->scale(factor);
      shapes[i]->move((before.x - after.x) * factor, (before.y - after.y) * factor);
    }
  }

  void outputData(const Shape * const * const shapes)
  {
    for(std::size_t i = 0; i < SIZE; i++)
    {
      std::cout << "-------SHAPE " << i << "-------\n";
      std::cout << "Area: " << shapes[i]->getArea() << "\n";

      const rectangle_t currRect = shapes[i]->getFrameRect();
      std::cout << "Rectangle:\n";
      std::cout << "width: " << currRect.width << "\n";
      std::cout << "height: " << currRect.height << "\n";
      std::cout << "center: (" << currRect.pos.x << ", " << currRect.pos.y << ")\n";
    }

    std::cout << "---------------------\n";
    std::cout << "Total Area: " << getTotalArea(shapes);

    const rectangle_t totalRect = getTotalFrameRect(shapes);
    std::cout << "\nTotal Frame Rectangle:\n";
    std::cout << "width: " << totalRect.width << "\n";
    std::cout << "height: " << totalRect.height << "\n";
    std::cout << "center: (" << totalRect.pos.x << ", " << totalRect.pos.y << ")\n";
  }
}

int main()
{
  korotkin::Shape* shapes[SIZE]{};
  try
  {
    shapes[0] = new korotkin::Rectangle(RECTANGLE_WIDTH, RECTANGLE_HEIGHT, RECTANGLE_CENTER);
    shapes[1] = new korotkin::Ring(RING_OUTER_RADIUS, RING_INNER_RADIUS, RING_CENTER);
    shapes[2] = new korotkin::Concave(CONCAVE_A, CONCAVE_B, CONCAVE_C, CONCAVE_D);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';

    deleteShapes(shapes);

    return ALLOCATION_ERROR;
  }

  korotkin::point_t scalePoint{};
  double scaleFactor = 0;
  std::cin >> scalePoint.x >> scalePoint.y >> scaleFactor;

  if (std::cin.fail() || scaleFactor <= 0)
  {
    std::cerr << "ERROR: scale must be a positive number" << '\n';
    return INPUT_ERROR;
  }

  outputData(shapes);
  scaleAroundPoint(shapes, scalePoint, scaleFactor);
  std::cout << "\n\n";
  outputData(shapes);

  deleteShapes(shapes);

  return 0;
}
