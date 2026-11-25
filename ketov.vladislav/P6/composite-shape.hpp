#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <cstddef>
#include <stdexcept>
#include "../common/shape.hpp"

namespace ketov
{
  class CompositeShape
  {
  public:
    CompositeShape() noexcept = default;
    ~CompositeShape();

    CompositeShape(const CompositeShape &other);
    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;
    CompositeShape &operator=(CompositeShape &&other) noexcept;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;

    void reserve(std::size_t new_cap);
    void shrink();

    Shape &at(std::size_t index);
    const Shape &at(std::size_t index) const;
    Shape &get(std::size_t index) noexcept;
    const Shape &get(std::size_t index) const noexcept;
    Shape &first();
    const Shape &first() const;
    Shape &last();
    const Shape &last() const;

    void append(Shape *shape);
    void preappend(Shape *shape);
    void add(std::size_t index, Shape *shape);
    void remove(std::size_t index);
    void dropFirst();
    void dropLast();

  private:
    void copy(Shape **dest, const Shape *const *src, std::size_t count) const;

    Shape **data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
  };
}

#endif
