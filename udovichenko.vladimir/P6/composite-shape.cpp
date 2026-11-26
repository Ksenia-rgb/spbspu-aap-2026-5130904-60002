#include "composite-shape.hpp"
#include <limits>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace udovichenko
{
  CompositeShape::CompositeShape(IShape *shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Shape cannot be nullptr");
    }
    size_ = 1;
    shapes_ = new IShape *[size_]();
    shapes_[0] = shape;
  }

  CompositeShape::CompositeShape(const CompositeShape &other)
  {
    if (other.empty())
    {
      size_ = 0;
      shapes_ = nullptr;
      return;
    }
    size_ = other.size_;
    shapes_ = new IShape *[size_]();
    try
    {
      for (std::size_t i = 0; i < size_; i++)
      {
        shapes_[i] = other.shapes_[i]->clone();
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&other) noexcept
  {
    swap(other);
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this != &other)
    {
      CompositeShape temp(other);
      swap(temp);
    }
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this != &other)
    {
      clear();
      swap(other);
    }
    return *this;
  }

  CompositeShape::~CompositeShape()
  {
    clear();
  }

  void CompositeShape::add(std::size_t index, IShape *shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Shape cannot be nullptr");
    }
    if (index > size_)
    {
      throw std::out_of_range("Index out of range");
    }

    const auto temp = new IShape *[size_ + 1]();
    if (shapes_)
    {
      std::copy(shapes_, shapes_ + index, temp);
      std::copy(shapes_ + index, shapes_ + size_, temp + index + 1);
    }
    temp[index] = shape;

    delete[] shapes_;
    size_++;
    shapes_ = temp;
  }

  void CompositeShape::preappend(IShape *shape)
  {
    add(0, shape);
  }

  void CompositeShape::append(IShape *shape)
  {
    add(size_, shape);
  }

  void CompositeShape::remove(std::size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index out of range");
    }
    if (size_ == 1)
    {
      size_ = 0;
      delete shapes_[0];
      delete[] shapes_;
      shapes_ = nullptr;
      return;
    }
    const auto temp = new IShape *[size_ - 1]();
    std::copy(shapes_, shapes_ + index, temp);
    std::copy(shapes_ + index + 1, shapes_ + size_, temp + index);
    delete shapes_[index];
    delete[] shapes_;
    size_--;
    shapes_ = temp;
  }

  void CompositeShape::dropFirst()
  {
    if (empty())
    {
      return;
    }
    remove(0);
  }

  void CompositeShape::dropLast()
  {
    if (empty())
    {
      return;
    }
    remove(size_ - 1);
  }

  void CompositeShape::clear()
  {
    for (std::size_t i = 0; i < size_; i++)
    {
      delete shapes_[i];
      shapes_[i] = nullptr;
    }
    delete[] shapes_;
    size_ = 0;
    shapes_ = nullptr;
  }

  IShape &CompositeShape::get(std::size_t index) noexcept
  {
    return *shapes_[index];
  }

  const IShape &CompositeShape::get(std::size_t index) const noexcept
  {
    return *shapes_[index];
  }

  IShape &CompositeShape::at(std::size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index out of range");
    }
    return *shapes_[index];
  }

  const IShape &CompositeShape::at(std::size_t index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index out of range");
    }
    return *shapes_[index];
  }

  IShape &CompositeShape::last()
  {
    return at(size_ - 1);
  }

  const IShape &CompositeShape::last() const
  {
    return at(size_ - 1);
  }

  IShape &CompositeShape::first()
  {
    return at(0);
  }

  const IShape &CompositeShape::first() const
  {
    return at(0);
  }

  std::size_t CompositeShape::size() const noexcept
  {
    return size_;
  }

  bool CompositeShape::empty() const noexcept
  {
    return size_ == 0;
  }

  void CompositeShape::swap(CompositeShape &other) noexcept
  {
    std::swap(size_, other.size_);
    std::swap(shapes_, other.shapes_);
  }
}
