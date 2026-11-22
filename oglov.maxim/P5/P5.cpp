#include <iostream>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "xquare.hpp"
#include "rubber.hpp"
namespace oglov
{
  void printFrameRect(const rectangle_t& r)
  {
    std::cout << "width = " << r.width << ", height = " << r.height << ", position = { " << r.pos.x << ", " << r.pos.y
              << " }\n";
  }
  double max(double a, double b)
  {
    if (a > b)
    {
      return a;
    }
    return b;
  }
  double min(double a, double b)
  {
    if (a < b)
    {
      return a;
    }
    return b;
  }
  rectangle_t commonFramerectangle(Shape* const* shapes)
  {
    rectangle_t init = shapes[0]->getFrameRect();
    double minX = init.pos.x - init.width / 2.0;
    double maxX = init.pos.x + init.width / 2.0;
    double minY = init.pos.y - init.height / 2.0;
    double maxY = init.pos.y + init.height / 2.0;

    for (size_t i = 1; i < 3; ++i)
    {
      init = shapes[i]->getFrameRect();
      minX = min(minX, init.pos.x - init.width / 2.0);
      maxX = max(maxX, init.pos.x + init.width / 2.0);
      minY = min(minY, init.pos.y - init.height / 2.0);
      maxY = max(maxY, init.pos.y + init.height / 2.0);
    }

    return rectangle_t{maxX - minX, maxY - minY, {(maxX + minX) / 2.0, (maxY + minY) / 2.0}};
  }
  void printShape(Shape* const* shapes)
  {
    std::cout << "Rectangle: \n";
    std::cout << "Area = " << shapes[0]->getArea() << "\nRectangle frame Rectangle: ";
    oglov::printFrameRect(shapes[0]->getFrameRect());
    std::cout << "Xquare: \n";
    std::cout << "Area = " << shapes[1]->getArea() << "\nXquare frame Rectangle: ";
    oglov::printFrameRect(shapes[1]->getFrameRect());
    std::cout << "Rubber: \n";
    std::cout << "Area = " << shapes[2]->getArea() << "\nRubber frame Rectangle: ";
    oglov::printFrameRect(shapes[2]->getFrameRect());
    double sumArea = 0.0;
    for (size_t i = 0; i < 3; i++)
    {
      sumArea += shapes[i]->getArea();
    }
    std::cout << "\n\nSumArea = " << sumArea << ", common frame rectangle: ";
    oglov::printFrameRect(oglov::commonFramerectangle(shapes));
  }
}
int main()
{
  Shape* shapes[3];
  try
  {
    shapes[0] = new Rectangle(3.0, 4.0, {1.0, 1.0});
    shapes[1] = new Xquare(7.0, {2.0, 2.0});
    shapes[2] = new Rubber(5.0, {-1.0, -1.0}, 2.0, {0.0, 0.0});

    oglov::printShape(shapes);

    double x;
    double y;
    double k;
    if (!(std::cin >> k >> x >> y))
    {
      std::cerr << "Invalid input";
      return 1;
    }

    for (size_t i = 0; i < 3; i++)
    {
      shapes[i]->move({x, y});
      shapes[i]->scale(k);
    }

    oglov::printShape(shapes);

    for (size_t i = 0; i < 3; i++)
    {
      delete shapes[i];
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
