#ifndef ASCII_STRING_HPP
#define ASCII_STRING_HPP
#include <cstddef>

namespace udovichenko
{
  class ASCIIString
  {
  public:
    ASCIIString();
    ASCIIString(const char *str);
    ASCIIString(const ASCIIString &str);
    ASCIIString &operator=(const ASCIIString &str);
    ASCIIString(ASCIIString &&str) noexcept;
    ASCIIString &operator=(ASCIIString &&str) noexcept;
    ~ASCIIString();

    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;

    std::size_t size() const;
    std::size_t capacity() const;
    char *data();
    const char *data() const;
    const char *cStr() const;
    char &at(std::size_t index);
    const char &at(std::size_t index) const;
    void insert(std::size_t index, const char *str);
    void append(char c);
    void erase();
    void erase(std::size_t index, std::size_t count);

  private:
    std::size_t size_;
    std::size_t capacity_;
    char *data_;

    std::size_t calculateNewCapacity(std::size_t required_size) const;
    void reserve(std::size_t new_capacity);
  };
}

#endif
