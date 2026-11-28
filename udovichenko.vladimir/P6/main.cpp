#include <iostream>
#include <stdexcept>
#include "../common/rectangle.hpp"
#include "../common/diamond.hpp"
#include "../common/triangle.hpp"
#include "shape-functions.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    udovichenko::CompositeShape shapes;
    shapes.append(new udovichenko::Rectangle{2, 2, {1, 0}});
    shapes.append(new udovichenko::Diamond{3, 1, {4, 4}});
    shapes.append(new udovichenko::Triangle{{0, 4}, {4, 0}, {0, 2}});
    shapes.append(new udovichenko::Rectangle{{1, 1}, {3, 3}});
    udovichenko::printShapes(shapes);

    double scale_factor = 1.0;
    udovichenko::point_t scale_center;
    if (!(std::cin >> scale_center.x >> scale_center.y >> scale_factor) || scale_factor <= 0.0)
    {
      throw std::runtime_error("Invalid input for scale point (x, y) or scale factor");
    }
    udovichenko::allotropicScaleShapes(shapes, scale_center, scale_factor);
    udovichenko::printShapes(shapes);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
