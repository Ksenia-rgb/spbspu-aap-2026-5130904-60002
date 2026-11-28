#include <iostream>
#include <algorithm>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "bubble.hpp"
#include "complexquad.hpp"

namespace budakov
{
  const int SIZE = 3;

  void freeShapes(Shape** arr, int size)
  {
    for (int i = 0; i < size; i++)
    {
      delete arr[i];
      arr[i] = nullptr;
    }
    delete[] arr;
    arr = nullptr;
  }

  double getSumArea(Shape** arr, int size)
  {
    double sum_area = 0;

    for (int i = 0; i < size; i++)
    {
      sum_area += arr[i]->getArea();
    }
    return sum_area;
  }

  rectangle_t getSumFrameRect(Shape** arr, int size)
  {
    double min_x = arr[0]->getFrameRect().pos.x - 0.5 * arr[0]->getFrameRect().width;
    double max_x = arr[0]->getFrameRect().pos.x + 0.5 * arr[0]->getFrameRect().width;
    double min_y = arr[0]->getFrameRect().pos.y - 0.5 * arr[0]->getFrameRect().height;
    double max_y = arr[0]->getFrameRect().pos.y + 0.5 * arr[0]->getFrameRect().height;

    for (int i = 0; i < size; i++)
    {
      double cmin_x = arr[i]->getFrameRect().pos.x - 0.5 * arr[i]->getFrameRect().width;
      double cmax_x = arr[i]->getFrameRect().pos.x + 0.5 * arr[i]->getFrameRect().width;
      double cmin_y = arr[i]->getFrameRect().pos.y - 0.5 * arr[i]->getFrameRect().height;
      double cmax_y = arr[i]->getFrameRect().pos.y + 0.5 * arr[i]->getFrameRect().height;

      min_x = std::min(cmin_x, min_x);
      max_x = std::max(cmax_x, max_x);
      min_y = std::min(cmin_y, min_y);
      max_y = std::max(cmax_y, max_y);
    }

    double width = max_x - min_x;
    double height = max_y - min_y;

    return {width, height, {min_x + 0.5 * max_x, min_y + 0.5 * max_y}};
  }

  void scaleFromPoint(Shape* shape, const point_t& point, double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Wrong factor\n");
    }

    const budakov::point_t frame1 = shape->getFrameRect().pos;
    shape->move(point);
    shape->scale(factor);
    const budakov::point_t frame2 = shape->getFrameRect().pos;

    const double dx = (point.x + (frame1.x - point.x) * factor) - frame2.x;
    const double dy = (point.y + (frame1.y - point.y) * factor) - frame2.y;
    shape->move(dx, dy);
  }

  void printShapes(Shape** arr, int size)
  {
    for (int i = 0; i < size; i++)
    {
      std::cout << i + 1 << ") Area: " << arr[i]->getArea() << "\n";
    }
    std::cout << "Sum area: " << getSumArea(arr, size) << "\n";

    for (int i = 0; i < size; i++)
    {
      const rectangle_t rect = arr[i]->getFrameRect();
      std::cout << "Frame Rectangles: \n";
      std::cout << i + 1 << ") Height: " << rect.height << ", Width: " << rect.width << ", Center: " << rect.pos.x << " " << rect.pos.y << "\n";
    }
    rectangle_t sum_rect = getSumFrameRect(arr, size);
    std::cout << "Sum Frame Rectangle: \n";
    std::cout << "Height: " << sum_rect.height << ", Width: " << sum_rect.width << ", Center: " << sum_rect.pos.x;
    std::cout << " " << sum_rect.pos.y << "\n";
  }
}

int main()
{
  budakov::Shape** shps = nullptr;
  int size = budakov::SIZE;
  try
  {
    shps = new budakov::Shape*[size]();
    shps[0] = new budakov::Rectangle(12.0, 20.0, {2.0, 2.0});
    shps[1] = new budakov::Bubble(3.0, {3.0, 3.0}, {4.2, 3.6});
    shps[2] = new budakov::Complexquad({0.0, 0.0}, {4.0, 4.0}, {4.0, 0.0}, {0.0, 4.0});

    std::cout << "~~~~ Before ~~~~\n";
    budakov::printShapes(shps, size);

    std::cout << "\nEnter parameters (x, y, k) for scaling: ";
    budakov::point_t point{};
    double factor = 0.0;
    if (!(std::cin >> point.x >> point.y >> factor))
    {
      throw std::invalid_argument("Wrong parameters\n");
    }

    for (int i = 0; i < size; i++)
    {
      budakov::scaleFromPoint(shps[i], point, factor);
    }

    std::cout << "~~~~ After ~~~~\n";
    budakov::printShapes(shps, size);
  }
  catch(const std::exception& e)
  {
    std::cerr << "ERROR: " << e.what();
    budakov::freeShapes(shps, size);

    return 1;
  }


  return 0;
}
