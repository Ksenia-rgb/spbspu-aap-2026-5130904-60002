#include <cctype>
#include <iostream>
#include <new>
#include <iostream>

namespace shakirov {

  const size_t firstMemory = 2;
  const size_t asciiSize = 256;
  const size_t latinCount = 26;
  int readChar(std::istream& in, char* result)
  {
    char ch = '\0';
    while (in.get(ch)) {
      if (!std::isspace(static_cast< unsigned char >(ch))) {
        *result = ch;
        return 0;
      }
    }
    return 1;
  }
  int readLine(std::istream& in, char** const result)
  {
    size_t capacity = firstMemory;
    size_t size = 0;
    char* line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return 1;
    }
    char ch = '\0';
    while (in.get(ch) && ch != '\n') {
      if (size + 1 >= capacity) {
        const size_t newCapacity = capacity * 2;
        char* const bigger = new (std::nothrow) char[newCapacity];
        if (bigger == nullptr) {
          delete[] line;
          return 1;
        }
        for (size_t i = 0; i < size; i++) {
          bigger[i] = line[i];
        }
        delete[] line;
        line = bigger;
        capacity = newCapacity;
      }
      line[size] = ch;
      size++;
    }
    line[size] = '\0';
    *result = line;
    return 0;
  }
  char* replace(const char* s, char a, char b, char* out)
  {
    size_t k = 0;
    for (const char* p = s; *p != '\0'; ++p) {
      out[k++] = (*p == a) ? b : *p;
    }
    out[k] = '\0';
    return out;
  }
  char* topThreeFrequent(const char* s, char* out)
  {
    int count[asciiSize] = {};
    for (const char* p = s; *p != '\0'; ++p) {
      unsigned char c = static_cast< unsigned char >(*p);
      if (std::isalpha(c)) {
        ++count[c];
      }
    }

    unsigned char top[3];
    size_t k = 0;
    for (size_t round = 0; round < 3; ++round) {
      int best = -1;
      for (int code = 0; code < static_cast< int >(asciiSize); ++code) {
        if (count[code] > 0 && (best == -1 || count[code] > count[best])) {
          best = code;
        }
      }
      if (best == -1) {
        break;
      }
      top[k++] = static_cast< unsigned char >(best);
      count[best] = 0;
    }

    for (size_t i = 0; i < k; ++i) {
      for (size_t j = i + 1; j < k; ++j) {
        if (top[j] < top[i]) {
          unsigned char t = top[i];
          top[i] = top[j];
          top[j] = t;
        }
      }
    }

    for (size_t i = 0; i < k; ++i) {
      out[i] = static_cast< char >(top[i]);
    }
    out[k] = '\0';
    return out;
  }

}

int main()
{
  char* line = nullptr;
  char* replaced = nullptr;
  char* frequent = nullptr;
  try {
    if (shakirov::readLine(std::cin, &line) != 0) {
      throw std::runtime_error("cannot allocate memory");
    }
    if (line[0] == '\0') {
      throw std::runtime_error("empty input");
    }
    char oldChar = '\0';
    char newChar = '\0';
    if (shakirov::readChar(std::cin, &oldChar) != 0) {
      throw std::runtime_error("no character to replace");
    }
    if (shakirov::readChar(std::cin, &newChar) != 0) {
      throw std::runtime_error("no new character");
    }

    replaced = new char[std::char_traits< char >::length(line) + 1];
    frequent = new char[4];
    std::cout << shakirov::replace(line, oldChar, newChar, replaced) << "\n";
    std::cout << shakirov::topThreeFrequent(line, frequent) << "\n";
  } catch (const std::bad_alloc&) {
    std::cerr << "Error: cannot allocate memory\n";
    delete[] replaced;
    delete[] line;
    delete[] frequent;
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    delete[] replaced;
    delete[] line;
    delete[] frequent;
    return 1;
  }
  delete[] replaced;
  delete[] line;
  delete[] frequent;
  return 0;
}
