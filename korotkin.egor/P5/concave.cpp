#include "concave.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace
{
  const int REFLEX_COUNT = 1;
  const double HALF = 0.5;
}

namespace korotkin
{
  double Concave::cross(point_t a, point_t b, point_t c) const
  {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  }

  Concave::Concave(point_t a, point_t b, point_t c, point_t d):
    vertices_{a, b, c, d}
  {
    if (getReflexIndex() == VERTICES_NUMBER)
    {
      throw std::invalid_argument("ERROR: vertices must form a valid concave quadrilateral");
    }
  }

  std::size_t Concave::getReflexIndex() const
  {
    double turns[VERTICES_NUMBER] = {};
    std::size_t positive = 0;
    std::size_t negative = 0;

    for (std::size_t i = 0; i < VERTICES_NUMBER; i++)
    {
      const std::size_t mid = (i + 1) % VERTICES_NUMBER;
      const std::size_t last = (mid + 1) % VERTICES_NUMBER;

      turns[mid] = cross(vertices_[i], vertices_[mid], vertices_[last]);

      if (turns[mid] == 0)
      {
        return VERTICES_NUMBER;
      }
      if (turns[mid] > 0)
      {
        positive++;
      }
      else
      {
        negative++;
      }
    }

    if (positive != REFLEX_COUNT && negative != REFLEX_COUNT)
    {
      return VERTICES_NUMBER;
    }

    const bool reflexPositive = (positive == REFLEX_COUNT);
    for (std::size_t i = 0; i < VERTICES_NUMBER; i++)
    {
      if ((turns[i] > 0) == reflexPositive)
      {
        return i;
      }
    }

    return VERTICES_NUMBER;
  }

  double Concave::getArea() const
  {
    double sum = 0;

    for (std::size_t i = 0; i < VERTICES_NUMBER; i++)
    {
      const std::size_t j = (i + 1) % VERTICES_NUMBER;
      sum += vertices_[i].x * vertices_[j].y - vertices_[j].x * vertices_[i].y;
    }

    const double area = std::abs(sum) * HALF;

    return area;
  }

  rectangle_t Concave::getFrameRect() const
  {
    double minX = vertices_[0].x;
    double maxX = vertices_[0].x;
    double minY = vertices_[0].y;
    double maxY = vertices_[0].y;

    for (std::size_t i = 1; i < VERTICES_NUMBER; i++)
    {
      if (vertices_[i].x < minX)
      {
        minX = vertices_[i].x;
      }

      if (vertices_[i].x > maxX)
      {
        maxX = vertices_[i].x;
      }

      if (vertices_[i].y < minY)
      {
        minY = vertices_[i].y;
      }
      if (vertices_[i].y > maxY)
      {
        maxY = vertices_[i].y;
      }
    }

    const double centerX = (minX + maxX) / 2;
    const double centerY = (minY + maxY) / 2;

    return rectangle_t{maxX - minX, maxY - minY, point_t{centerX, centerY}};
  }

  void Concave::move(point_t p)
  {
    const point_t center = vertices_[getReflexIndex()];
    move(p.x - center.x, p.y - center.y);
  }

  void Concave::move(double x, double y)
  {
    for (std::size_t i = 0; i < VERTICES_NUMBER; i++)
    {
      vertices_[i].x += x;
      vertices_[i].y += y;
    }
  }

  void Concave::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("ERROR: scale must be positive");
    }

    const point_t center = vertices_[getReflexIndex()];
    for (std::size_t i = 0; i < VERTICES_NUMBER; i++)
    {
      vertices_[i].x = center.x + (vertices_[i].x - center.x) * k;
      vertices_[i].y = center.y + (vertices_[i].y - center.y) * k;
    }
  }
}

