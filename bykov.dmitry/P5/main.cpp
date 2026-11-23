#include <cctype>
#include <exception>
#include <iostream>
#include <istream>
#include <memory>
#include <new>
#include <cstddef>
#include "base-types.hpp"
#include "diamond.hpp"
#include "geometry.hpp"
#include "rectangle.hpp"
#include "ring.hpp"
#include "shape.hpp"

namespace bykov
{
  static bool readNumber(std::istream& input, double& value)
  {
    if (!(input >> value))
    {
      return false;
    }
    const int next = input.peek();
    return input.eof() || std::isspace(next);
  }
}

int main()
{
  const int error_code = 1;
  try
  {
    constexpr double rectangle_width = 4.0;
    constexpr double rectangle_height = 2.0;
    constexpr double inner_radius = 1.0;
    constexpr double outer_radius = 3.0;
    constexpr double diagonal_x = 6.0;
    constexpr double diagonal_y = 4.0;
    constexpr double offset = 5.0;
    const auto rectangle
        = std::make_unique< bykov::Rectangle >(bykov::point_t{0.0, 0.0}, rectangle_width, rectangle_height);
    const auto ring = std::make_unique< bykov::Ring >(bykov::point_t{offset, 0.0}, inner_radius, outer_radius);
    const auto diamond = std::make_unique< bykov::Diamond >(bykov::point_t{0.0, offset}, diagonal_x, diagonal_y);
    bykov::Shape* const shapes[] = {rectangle.get(), ring.get(), diamond.get()};
    const std::size_t count = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << "Before\n";
    bykov::printShapes(std::cout, shapes, count);

    bykov::point_t center = {};
    double factor = 0.0;
    if (!bykov::readNumber(std::cin, center.x) || !bykov::readNumber(std::cin, center.y)
        || !bykov::readNumber(std::cin, factor))
    {
      std::cerr << "Error: expected center x, center y and scale factor\n";
      return error_code;
    }
    bykov::scaleShapes(shapes, count, center, factor);
    std::cout << "After\n";
    bykov::printShapes(std::cout, shapes, count);
    if (!std::cout)
    {
      std::cerr << "Error: cannot write shape parameters\n";
      return error_code;
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: not enough memory for shapes\n";
    return error_code;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return error_code;
  }
  return 0;
}
