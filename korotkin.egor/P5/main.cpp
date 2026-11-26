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
  void deleteShapes(const Shape *const *shapes)
  {
    if (shapes)
    {
      for (std::size_t i = 0; i < SIZE; i++)
      {
        delete shapes[i];
      }
    }
  }

  double getTotalArea(const Shape *const *shapes)
  {
    double sum = 0;

    for (std::size_t i = 0; i < SIZE; i++)
    {
      sum += shapes[i]->getArea();
    }

    return sum;
  }

  rectangle_t getTotalFrameRect(const Shape *const *shapes)
  {
    const rectangle_t first = shapes[0]->getFrameRect();
    double min_x = first.pos.x - (first.width / 2);
    double max_x = first.pos.x + (first.width / 2);
    double min_y = first.pos.y - (first.height / 2);
    double max_y = first.pos.y + (first.height / 2);

    for (std::size_t i = 1; i < SIZE; i++)
    {
      const rectangle_t curr = shapes[i]->getFrameRect();
      const double curr_min_x = curr.pos.x - curr.width / 2;
      const double curr_max_x = curr.pos.x + curr.width / 2;
      const double curr_min_y = curr.pos.y - curr.height / 2;
      const double curr_max_y = curr.pos.y + curr.height / 2;

      min_x = std::min(min_x, curr_min_x);
      max_x = std::max(max_x, curr_max_x);
      min_y = std::min(min_y, curr_min_y);
      max_y = std::max(max_y, curr_max_y);
    }

    const double width = max_x - min_x;
    const double height = max_y - min_y;
    const point_t center{(min_x + max_x) / 2, (min_y + max_y) / 2};

    return rectangle_t{width, height, center};
  }

  void scaleAroundPoint(Shape *const *shapes, point_t point, double factor)
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

  void outputData(const Shape *const *shapes)
  {
    for (std::size_t i = 0; i < SIZE; i++)
    {
      std::cout << "-------SHAPE " << i << "-------\n";
      std::cout << "Area: " << shapes[i]->getArea() << "\n";

      const rectangle_t curr_rect = shapes[i]->getFrameRect();
      std::cout << "Rectangle:\n";
      std::cout << "width: " << curr_rect.width << "\n";
      std::cout << "height: " << curr_rect.height << "\n";
      std::cout << "center: (" << curr_rect.pos.x << ", " << curr_rect.pos.y << ")\n";
    }

    std::cout << "---------------------\n";
    std::cout << "Total Area: " << getTotalArea(shapes);

    const rectangle_t total_rect = getTotalFrameRect(shapes);
    std::cout << "\nTotal Frame Rectangle:\n";
    std::cout << "width: " << total_rect.width << "\n";
    std::cout << "height: " << total_rect.height << "\n";
    std::cout << "center: (" << total_rect.pos.x << ", " << total_rect.pos.y << ")\n";
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

  outputData(shapes);

  korotkin::point_t scale_point{};
  double scale_factor = 0;
  std::cin >> scale_point.x >> scale_point.y >> scale_factor;

  if (std::cin.fail() || scale_factor <= 0)
  {
    std::cerr << "ERROR: scale must be a positive number" << '\n';

    deleteShapes(shapes);

    return INPUT_ERROR;
  }

  scaleAroundPoint(shapes, scale_point, scale_factor);
  std::cout << "\n\n";
  outputData(shapes);

  deleteShapes(shapes);

  return 0;
}
