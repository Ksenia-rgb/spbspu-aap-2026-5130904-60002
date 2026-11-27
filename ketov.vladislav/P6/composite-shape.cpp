#include "composite-shape.hpp"

namespace ketov
{
  CompositeShape::~CompositeShape()
  {
    clear();
    delete[] data_;
  }

  CompositeShape::CompositeShape(const CompositeShape &other)
  {
    if (other.size_ > 0)
    {
      data_ = new Shape *[other.size_];
      try
      {
        copy(data_, other.data_, other.size_);
      }
      catch (...)
      {
        delete[] data_;
        data_ = nullptr;
        throw;
      }
      capacity_ = other.size_;
    }
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }

    Shape **new_data = nullptr;
    const std::size_t new_size = other.size_;

    if (other.data_ != nullptr)
    {
      new_data = new Shape *[new_size];
      copy(new_data, other.data_, new_size);
    }

    for (std::size_t i = 0; i < size_; i++)
    {
      delete data_[i];
    }
    delete[] data_;

    data_ = new_data;
    size_ = new_size;
    capacity_ = other.size_;

    return *this;
  }

  CompositeShape::CompositeShape(CompositeShape &&other) noexcept
  {
    size_ = other.size_;
    data_ = other.data_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }

    for (std::size_t i = 0; i < size_; i++)
    {
      delete data_[i];
    }
    delete[] data_;

    size_ = other.size_;
    data_ = other.data_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
  }

  std::size_t CompositeShape::size() const noexcept
  {
    return size_;
  }

  std::size_t CompositeShape::capacity() const noexcept
  {
    return capacity_;
  }

  bool CompositeShape::empty() const noexcept
  {
    return size_ == 0;
  }

  void CompositeShape::clear() noexcept
  {
    for (std::size_t i = 0; i < size_; i++)
    {
      delete data_[i];
    }
    size_ = 0;
  }

  void CompositeShape::reserve(std::size_t new_cap)
  {
    if (new_cap <= capacity_)
    {
      return;
    }
    Shape **const new_data = new Shape *[new_cap];
    for (std::size_t i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }

  void CompositeShape::shrink()
  {
    if (size_ == capacity_)
    {
      return;
    }
    if (size_ == 0)
    {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
      return;
    }
    Shape **const new_data = new Shape *[size_];
    for (std::size_t i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }

  Shape &CompositeShape::at(std::size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("index out of range");
    }
    return *data_[index];
  }

  const Shape &CompositeShape::at(std::size_t index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("index out of range");
    }
    return *data_[index];
  }

  Shape &CompositeShape::get(std::size_t index) noexcept
  {
    return *data_[index];
  }

  const Shape &CompositeShape::get(std::size_t index) const noexcept
  {
    return *data_[index];
  }

  Shape &CompositeShape::first()
  {
    if (empty())
    {
      throw std::out_of_range("empty shape");
    }
    return *data_[0];
  }

  const Shape &CompositeShape::first() const
  {
    if (empty())
    {
      throw std::out_of_range("empty shape");
    }
    return *data_[0];
  }

  Shape &CompositeShape::last()
  {
    if (empty())
    {
      throw std::out_of_range("empty shape");
    }
    return *data_[size_ - 1];
  }

  const Shape &CompositeShape::last() const
  {
    if (empty())
    {
      throw std::out_of_range("empty shape");
    }
    return *data_[size_ - 1];
  }

  void CompositeShape::append(Shape *shape)
  {
    add(size_, shape);
  }

  void CompositeShape::preappend(Shape *shape)
  {
    add(0, shape);
  }

  void CompositeShape::add(std::size_t index, Shape *shape)
  {
    if (index > size_)
    {
      throw std::out_of_range("index out of range");
    }
    if (shape == nullptr)
    {
      throw std::invalid_argument("shape is null");
    }

    reserve(size_ + 1);
    for (std::size_t i = size_; i > index; i--)
    {
      data_[i] = data_[i - 1];
    }
    data_[index] = shape;
    size_++;
  }

  void CompositeShape::remove(std::size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("index out of range");
    }

    delete data_[index];
    for (std::size_t i = index; i < size_ - 1; i++)
    {
      data_[i] = data_[i + 1];
    }
    size_--;
  }

  void CompositeShape::dropFirst()
  {
    remove(0);
  }
  void CompositeShape::dropLast()
  {
    if (empty())
    {
      throw std::out_of_range("empty shape");
    }
    remove(size_ - 1);
  }

  void CompositeShape::copy(Shape **dest, const Shape *const *src, std::size_t count) const
  {
    std::size_t cnt = 0;
    try
    {
      for (std::size_t i = 0; i < count; i++)
      {
        dest[i] = src[i]->clone();
        cnt++;
      }
    }
    catch (...)
    {
      for (std::size_t j = 0; j < cnt; j++)
      {
        delete dest[j];
      }
      throw;
    }
  }
}
