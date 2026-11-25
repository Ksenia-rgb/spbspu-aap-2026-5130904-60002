#include "ascii-string.hpp"
#include <cstring>
#include <stdexcept>
#include <limits>

namespace udovichenko
{
  ASCIIString::ASCIIString():
    size_(0),
    capacity_(0),
    data_(new char[capacity_ + 1]{})
  {}

  ASCIIString::ASCIIString(const char *str)
  {
    if (!str)
    {
      throw std::invalid_argument("Invalid string");
    }
    size_ = std::strlen(str);
    capacity_ = size_;
    data_ = new char[capacity_ + 1];
    std::strcpy(data_, str);
  }

  ASCIIString::ASCIIString(const ASCIIString &str):
    ASCIIString(str.cStr())
  {}

  ASCIIString &ASCIIString::operator=(const ASCIIString &str)
  {
    if (this == &str)
    {
      return *this;
    }
    if (!str.data())
    {
      delete[] data_;
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      return *this;
    }

    if (!data_ || capacity_ < str.size_)
    {
      char *const temp = new char[str.capacity_ + 1];
      std::memcpy(temp, str.data_, str.size_ + 1);
      delete[] data_;
      data_ = temp;
      capacity_ = str.capacity_;
    }
    else
    {
      std::memcpy(data_, str.data_, str.size_ + 1);
    }

    size_ = str.size_;
    return *this;
  }

  ASCIIString::ASCIIString(ASCIIString &&str) noexcept:
    size_(str.size_),
    capacity_(str.capacity_),
    data_(str.data_)
  {
    str.size_ = 0;
    str.capacity_ = 0;
    str.data_ = nullptr;
  }

  ASCIIString &ASCIIString::operator=(ASCIIString &&str) noexcept
  {
    if (this == &str)
    {
      return *this;
    }
    delete[] data_;
    size_ = str.size_;
    capacity_ = str.capacity_;
    data_ = str.data_;

    str.size_ = 0;
    str.capacity_ = 0;
    str.data_ = nullptr;
    return *this;
  }

  ASCIIString::~ASCIIString()
  {
    delete[] data_;
  }

  char &ASCIIString::operator[](std::size_t index)
  {
    return data_[index];
  }

  const char &ASCIIString::operator[](std::size_t index) const
  {
    return data_[index];
  }

  std::size_t ASCIIString::size() const
  {
    return size_;
  }

  std::size_t ASCIIString::capacity() const
  {
    return capacity_;
  }

  char *ASCIIString::data()
  {
    return data_;
  }

  const char *ASCIIString::data() const
  {
    return data_;
  }

  const char *ASCIIString::cStr() const
  {
    return data_ ? data_ : "";
  }

  char &ASCIIString::at(std::size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  const char &ASCIIString::at(std::size_t index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  void ASCIIString::insert(std::size_t index, const char *str)
  {
    if (!str)
    {
      return;
    }
    if (index > size_)
    {
      throw std::out_of_range("Index out of range");
    }
    const ASCIIString ascii_string{str};
    if (ascii_string.size_ == 0)
    {
      return;
    }
    if (ascii_string.size_ > std::numeric_limits< std::size_t >::max() - size_)
    {
      throw std::length_error("Max size exceeded");
    }
    const std::size_t new_size = size_ + ascii_string.size_;
    if (!data_ || new_size > capacity_)
    {
      reserve(calculateNewCapacity(new_size));
    }
    std::memmove(data_ + index + ascii_string.size_, data_ + index, size_ - index + 1);
    std::memcpy(data_ + index, ascii_string.data_, ascii_string.size_);
    size_ = new_size;
    data_[size_] = '\0';
  }

  void ASCIIString::append(char c)
  {
    if (size_ == std::numeric_limits< std::size_t >::max())
    {
      throw std::length_error("Max string length exceeded");
    }

    if (!data_ || size_ + 1 > capacity_)
    {
      reserve(calculateNewCapacity(size_ + 1));
    }

    data_[size_] = c;
    size_++;
    data_[size_] = '\0';
  }

  void ASCIIString::erase()
  {
    if (!data_)
    {
      return;
    }
    size_ = 0;
    data_[0] = '\0';
  }

  void ASCIIString::erase(std::size_t index, std::size_t count)
  {
    if (index > size_)
    {
      throw std::out_of_range("Index out of range");
    }
    if (count == 0 || index == size_)
    {
      return;
    }
    if (count > size_ - index)
    {
      count = size_ - index;
    }
    std::memmove(data_ + index, data_ + index + count, size_ - index - count + 1);
    size_ -= count;
  }

  std::size_t ASCIIString::calculateNewCapacity(std::size_t required_size) const
  {
    static constexpr std::size_t SMALL_CAPACITY = 4096;
    std::size_t new_capacity = capacity_;
    if (capacity_ == 0)
    {
      return required_size;
    }
    const std::size_t max_size = std::numeric_limits< std::size_t >::max();
    while (required_size > new_capacity)
    {
      std::size_t addition_capacity = new_capacity;
      if (new_capacity > SMALL_CAPACITY)
      {
        addition_capacity /= 2;
      }
      if (new_capacity > max_size - addition_capacity)
      {
        return required_size;
      }
      new_capacity += addition_capacity;
    }
    return new_capacity;
  }

  void ASCIIString::reserve(std::size_t new_capacity)
  {
    if (new_capacity <= capacity_)
    {
      return;
    }
    if (new_capacity == std::numeric_limits< std::size_t >::max())
    {
      throw std::length_error("Max capacity exceeded");
    }
    char *const temp = new char[new_capacity + 1];
    if (data_)
    {
      std::memcpy(temp, data_, size_);
    }
    temp[size_] = '\0';

    delete[] data_;
    data_ = temp;
    capacity_ = new_capacity;
  }
}
