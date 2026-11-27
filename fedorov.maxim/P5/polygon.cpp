
#include <stdexcept>

#include "polygon.hpp"
#include "base-types.hpp"
#include "geometry.hpp"

namespace fedorov
{
  const int SIX = 6;
  const int MIN_AREA = 1e-9;

  Polygon::Polygon(point_t* const vertices, const size_t size):
    vertices_count_(size),
    vertices_(nullptr)
  {
    if (vertices == nullptr)
    {
      throw std::invalid_argument("Vertices pointer cannot be null");
    }
    if (size < 3)
    {
      throw std::invalid_argument("Vertices count must be at least 3");
    }

    double signed_area = 0;
    double cx = 0;
    double cy = 0;
    size_t j = 0;
    for (size_t i = 0; i < size; ++i)
    {
      j = (i + 1) % size;
      const double cross = vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;

      signed_area += cross;
      cx += (vertices[i].x + vertices[j].x) * cross;
      cy += (vertices[i].y + vertices[j].y) * cross;
    }

    signed_area /= 2;

    if (std::abs(signed_area) < MIN_AREA)
    {
      throw std::invalid_argument("Polygon area cannot be zero");
    }

    cx /= (SIX * signed_area);
    cy /= (SIX * signed_area);

    center_ = {cx, cy};

    vertices_ = new point_t[size];
    for (size_t i = 0; i < size; i++)
    {
      vertices_[i] = vertices[i];
    }
  }

  Polygon::Polygon(const Polygon& other):
    vertices_count_(other.vertices_count_),
    center_(other.center_)
  {
    vertices_ = new point_t[other.vertices_count_];

    for (size_t i = 0; i < other.vertices_count_; i++)
    {
      vertices_[i] = other.vertices_[i];
    }
  }

  Polygon& Polygon::operator=(const Polygon& other) noexcept
  {
    if (&other == this)
    {
      return *this;
    }

    point_t* const new_vertices = new point_t[other.vertices_count_];
    for (size_t i = 0; i < other.vertices_count_; i++)
    {
      new_vertices[i] = other.vertices_[i];
    }
    delete[] vertices_;
    vertices_ = new_vertices;

    vertices_count_ = other.vertices_count_;
    center_ = other.center_;

    return *this;
  }

  Polygon& Polygon::operator=(Polygon&& other) noexcept
  {
    if (&other == this)
    {
      return *this;
    }

    vertices_count_ = other.vertices_count_;
    center_ = other.center_;

    delete[] vertices_;
    vertices_ = other.vertices_;
    other.vertices_ = nullptr;
    other.vertices_count_ = 0;
    return *this;
  }

  Polygon::~Polygon()
  {
    if (vertices_ != nullptr)
    {
      delete[] vertices_;
    }
  }

  double Polygon::getArea() const
  {
    double signed_area = 0;
    size_t j = 0;
    for (size_t i = 0; i < vertices_count_; i++)
    {
      j = (i + 1) % vertices_count_;
      signed_area += vertices_[i].x * vertices_[j].y - vertices_[j].x * vertices_[i].y;
    }

    return std::abs(signed_area) / 2;
  }

  rectangle_t Polygon::getFrameRect() const
  {
    return getFrameRectFromPoints(vertices_, vertices_count_);
  }

  void Polygon::move(const point_t new_pos)
  {
    move(new_pos.x - center_.x, new_pos.y - center_.y);
  }

  void Polygon::move(const double delta_x, const double delta_y)
  {
    if (delta_x == 0 && delta_y == 0)
    {
      return;
    }

    for (size_t i = 0; i < vertices_count_; i++)
    {
      vertices_[i].x += delta_x;
      vertices_[i].y += delta_y;
    }

    center_.x += delta_x;
    center_.y += delta_y;
  }

  void Polygon::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor must be positive");
    }
    for (size_t i = 0; i < vertices_count_; i++)
    {
      vertices_[i].x = center_.x + (vertices_[i].x - center_.x) * factor;
      vertices_[i].y = center_.y + (vertices_[i].y - center_.y) * factor;
    }
  }
}
