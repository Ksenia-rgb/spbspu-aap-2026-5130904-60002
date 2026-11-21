#ifndef ASCII_STRING_HPP
#define ASCII_STRING_HPP
#include <cstddef>

namespace bykov
{
  class AsciiString
  {
  public:
    AsciiString();
    AsciiString(const AsciiString& other);
    AsciiString(AsciiString&& other) noexcept;
    explicit AsciiString(const char* text);
    ~AsciiString();

    AsciiString& operator=(const AsciiString& other);
    AsciiString& operator=(AsciiString&& other) noexcept;
    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    const char* cStr() const noexcept;
    const char* data() const noexcept;
    char* data();
    void reserve(std::size_t capacity);
    void insert(std::size_t position, char character);
    void erase(std::size_t position, std::size_t count = 1);
    void append(char character);

  private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;
  };
}

#endif
