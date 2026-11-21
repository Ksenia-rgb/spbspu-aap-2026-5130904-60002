#include "ascii-string.hpp"
#include <cstring>
#include <limits>
#include <cstddef>
#include <stdexcept>

namespace bykov
{
  namespace
  {
    void checkAscii(char character)
    {
      constexpr unsigned char ascii_max = 127;
      if (character == '\0' || static_cast< unsigned char >(character) > ascii_max)
      {
        throw std::invalid_argument("Expected a nonzero ASCII character");
      }
    }
  }
}

bykov::AsciiString::AsciiString():
  data_(new char[1]{}),
  size_(0),
  capacity_(0)
{}

bykov::AsciiString::AsciiString(const char* text):
  AsciiString()
{
  if (text == nullptr)
  {
    throw std::invalid_argument("Null string pointer");
  }
  const std::size_t length = std::strlen(text);
  for (std::size_t i = 0; i < length; ++i)
  {
    checkAscii(text[i]);
  }
  reserve(length);
  std::memcpy(data_, text, length + 1);
  size_ = length;
}

bykov::AsciiString::AsciiString(const AsciiString& other):
  AsciiString(other.cStr())
{}

bykov::AsciiString::AsciiString(AsciiString&& other) noexcept:
  data_(other.data_),
  size_(other.size_),
  capacity_(other.capacity_)
{
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

bykov::AsciiString& bykov::AsciiString::operator=(const AsciiString& other)
{
  if (this != &other)
  {
    char* const copy = new char[other.size_ + 1];
    std::memcpy(copy, other.cStr(), other.size_ + 1);
    delete[] data_;
    data_ = copy;
    size_ = other.size_;
    capacity_ = other.size_;
  }
  return *this;
}

bykov::AsciiString& bykov::AsciiString::operator=(AsciiString&& other) noexcept
{
  if (this != &other)
  {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

bykov::AsciiString::~AsciiString()
{
  delete[] data_;
}

std::size_t bykov::AsciiString::size() const noexcept
{
  return size_;
}

std::size_t bykov::AsciiString::capacity() const noexcept
{
  return capacity_;
}

const char* bykov::AsciiString::cStr() const noexcept
{
  return data_ == nullptr ? "" : data_;
}

const char* bykov::AsciiString::data() const noexcept
{
  return cStr();
}

char* bykov::AsciiString::data()
{
  reserve(size_);
  return data_;
}

char& bykov::AsciiString::operator[](std::size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("String index is out of range");
  }
  return data_[index];
}

const char& bykov::AsciiString::operator[](std::size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("String index is out of range");
  }
  return data_[index];
}

void bykov::AsciiString::reserve(std::size_t capacity)
{
  if (capacity == std::numeric_limits< std::size_t >::max())
  {
    throw std::overflow_error("String capacity is too large");
  }
  if (capacity > capacity_ || data_ == nullptr)
  {
    char* const buffer = new char[capacity + 1];
    std::memcpy(buffer, cStr(), size_ + 1);
    delete[] data_;
    data_ = buffer;
    capacity_ = capacity;
  }
}

void bykov::AsciiString::insert(std::size_t position, char character)
{
  if (position > size_)
  {
    throw std::out_of_range("String insertion position is out of range");
  }
  checkAscii(character);
  if (size_ == capacity_)
  {
    constexpr std::size_t growth = 2;
    const std::size_t limit = std::numeric_limits< std::size_t >::max() - 1;
    if (size_ == limit)
    {
      throw std::overflow_error("String size is too large");
    }
    const std::size_t next = capacity_ >= limit / growth ? limit : capacity_ * growth + 1;
    reserve(next);
  }
  std::memmove(data_ + position + 1, data_ + position, size_ - position + 1);
  data_[position] = character;
  ++size_;
}

void bykov::AsciiString::erase(std::size_t position, std::size_t count)
{
  if (position > size_)
  {
    throw std::out_of_range("String erasure position is out of range");
  }
  if (count > size_ - position)
  {
    count = size_ - position;
  }
  if (data_ != nullptr)
  {
    std::memmove(data_ + position, data_ + position + count, size_ - position - count + 1);
    size_ -= count;
  }
}

void bykov::AsciiString::append(char character)
{
  insert(size_, character);
}
