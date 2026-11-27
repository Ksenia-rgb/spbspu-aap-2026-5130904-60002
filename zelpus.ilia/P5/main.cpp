#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "diamond.hpp"
#include "ellipse.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
namespace
{
  int rc = 0;
  const double one = 1.0;
  const double two = 2.0;
  const double three = 3.0;
  const double four = 4.0;
}
namespace zelpus
{
  void scaleAbout(Shape * const * const shapes, size_t n, const point_t & c, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("scale factor must be positive");
    }
    for (size_t i = 0; i < n; ++i)
    {
      const point_t prev = shapes[i]->getFrameRect().pos;
      shapes[i]->move(c);
      const double dx = c.x - prev.x;
      const double dy = c.y - prev.y;
      shapes[i]->scale(k);
      shapes[i]->move(-dx * k, -dy * k);
    }
  }

  rectangle_t totalFrame(const Shape * const * const shapes, size_t n)
  {
    rectangle_t f = shapes[0]->getFrameRect();
    double minX = f.pos.x - f.width / two;
    double maxX = f.pos.x + f.width / two;
    double minY = f.pos.y - f.height / two;
    double maxY = f.pos.y + f.height / two;
    for (size_t i = 1; i < n; ++i)
    {
      f = shapes[i]->getFrameRect();
      minX = std::min(minX, f.pos.x - f.width / two);
      maxX = std::max(maxX, f.pos.x + f.width / two);
      minY = std::min(minY, f.pos.y - f.height / two);
      maxY = std::max(maxY, f.pos.y + f.height / two);
    }
    return {maxX - minX, maxY - minY, {(minX + maxX) / two, (minY + maxY) / two}};
  }

  void printFrame(const rectangle_t & f)
  {
    std::cout << "  frame: width=" << f.width << " height=" << f.height << " center=(" << f.pos.x << ", " << f.pos.y
              << ")\n";
  }

  void printAll(const Shape * const * const shapes, size_t n)
  {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
      const double a = shapes[i]->getArea();
      sum += a;
      std::cout << "shape " << i << ": area=" << a << "\n";
      printFrame(shapes[i]->getFrameRect());
    }
    std::cout << "total area: " << sum << "\n";
    std::cout << "total";
    printFrame(totalFrame(shapes, n));
  }

  void deleteShapes(Shape ** const shapes, size_t n)

  {
    for (size_t i = 0; i < n; ++i)
    {
      delete shapes[i];
      shapes[i] = nullptr;
    }
  }
}

int main()
{
  const size_t N = 5;
  zelpus::Shape * shapes[N]{};
  try
  {
    shapes[0] = new zelpus::Rectangle(zelpus::point_t{0.0, 0.0}, four, two);
    shapes[1] = new zelpus::Rectangle(zelpus::point_t{-two, one}, two, three);
    shapes[2] = new zelpus::Diamond(zelpus::point_t{two, one}, four, four);
    shapes[3] = new zelpus::Diamond(zelpus::point_t{one, four}, two, four);
    shapes[4] = new zelpus::Ellipse(zelpus::point_t{-two, three}, three, one);

    zelpus::point_t c{0.0, 0.0};
    double k = 0.0;
    std::cout << "Enter point coordinates and factor: ";
    if (!(std::cin >> c.x >> c.y >> k))
    {
      throw std::invalid_argument("invalid input");
    }
    std::cout << "before:\n";
    zelpus::printAll(shapes, N);
    zelpus::scaleAbout(shapes, N, c, k);
    std::cout << "after:\n";
    zelpus::printAll(shapes, N);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    rc = 1;
  }
  zelpus::deleteShapes(shapes, N);
  return rc;
}

