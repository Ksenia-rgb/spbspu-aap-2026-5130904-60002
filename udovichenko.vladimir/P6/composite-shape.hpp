#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <cstddef>
#include "../common/shape.hpp"

namespace udovichenko
{
  class CompositeShape
  {
  public:
    CompositeShape() = default;
    CompositeShape(IShape *shape);
    CompositeShape(const CompositeShape &other);
    CompositeShape(CompositeShape &&other) noexcept;
    CompositeShape &operator=(const CompositeShape &other);
    CompositeShape &operator=(CompositeShape &&other) noexcept;
    ~CompositeShape();

    void add(std::size_t index, IShape *shape);
    void preappend(IShape *shape);
    void append(IShape *shape);

    void remove(std::size_t index);
    void dropFirst();
    void dropLast();
    void clear();

    IShape &get(std::size_t index) noexcept;
    const IShape &get(std::size_t index) const noexcept;
    IShape &at(std::size_t index);
    const IShape &at(std::size_t index) const;
    IShape &last();
    const IShape &last() const;
    IShape &first();
    const IShape &first() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    std::size_t size_ = 0;
    IShape **shapes_ = nullptr;

    void swap(CompositeShape &other) noexcept;
  };
}

#endif
