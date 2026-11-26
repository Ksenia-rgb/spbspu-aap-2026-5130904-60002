#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>

#include "base-types.hpp"
#include "shape.hpp"

namespace fedorov
{
  void scaleRelative(fedorov::Shape* shape, const fedorov::point_t point, const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor must be positive");
    }

    fedorov::point_t frame_before = shape->getFrameRect().pos;

    shape->move(point);

    fedorov::point_t frame_at_point = shape->getFrameRect().pos;
    fedorov::point_t true_center
        = {frame_before.x - (frame_at_point.x - point.x), frame_before.y - (frame_at_point.y - point.y)};

    shape->scale(factor);
    shape->move((true_center.x - point.x) * factor, (true_center.y - point.y) * factor);
  }

  fedorov::rectangle_t getFrameRectFromPoints(const fedorov::point_t* points, size_t size)
  {
    if (size < 3)
    {
      throw std::invalid_argument("Size of points list must be at least 3");
    }
    double min_x = points[0].x;
    double max_x = points[0].x;
    double min_y = points[0].y;
    double max_y = points[0].y;

    for (size_t i = 0; i < size; i++)
    {
      if (points[i].x < min_x)
      {
        min_x = points[i].x;
      }
      else if (points[i].x > max_x)
      {
        max_x = points[i].x;
      }
      if (points[i].y < min_y)
      {
        min_y = points[i].y;
      }
      else if (points[i].y > max_y)
      {
        max_y = points[i].y;
      }
    }
    return {max_y - min_y, max_x - min_x, {(min_x + max_x) / 2, (min_y + max_y) / 2}};
  }

  double getShapesArea(fedorov::Shape** shapes, size_t size)
  {
    double sum = 0;
    for (size_t i = 0; i < size; i++)
    {
      sum += shapes[i]->getArea();
    }
    return sum;
  }

  fedorov::rectangle_t getShapesFrameRect(fedorov::Shape** shapes, size_t size)
  {
    fedorov::point_t* points = new fedorov::point_t[size * 4];
    fedorov::rectangle_t rect;
    for (size_t i = 0; i < size; i++)
    {
      rect = shapes[i]->getFrameRect();
      points[i * 4] = {rect.pos.x - rect.width / 2, rect.pos.y - rect.height / 2};
      points[i * 4 + 1] = {rect.pos.x - rect.width / 2, rect.pos.y + rect.height / 2};
      points[i * 4 + 2] = {rect.pos.x + rect.width / 2, rect.pos.y - rect.height / 2};
      points[i * 4 + 3] = {rect.pos.x + rect.width / 2, rect.pos.y + rect.height / 2};
    }

    try
    {
      rect = getFrameRectFromPoints(points, size * 4);
    }
    catch (...)
    {
      delete[] points;
      points = nullptr;
    }

    if (points != nullptr)
    {
      delete[] points;
      points = nullptr;
    }

    return rect;
  }
}

#endif
