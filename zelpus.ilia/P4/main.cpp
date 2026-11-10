#include <iostream>
#include <cctype>
#include <new>

namespace zelpus {
  const char secondUnc[] = "abc_ef";
  const char secondLat[] = "def_ghk";
  const size_t firstMemory = 2;
  const size_t asciiSize = 256;
  const int ascii_limit = 128;
  const size_t latinCount = 26;

  char* findUncommonChars(char* const dest, const char* const str1, const char* const str2)
  {
    int in1[asciiSize] = {0};
    int in2[asciiSize] = {0};

    for (size_t i = 0; str1[i] != '\0'; i++) {
      in1[static_cast< unsigned char >(str1[i])] = 1;
    }
    for (size_t i = 0; str2[i] != '\0'; i++) {
      in2[static_cast< unsigned char >(str2[i])] = 1;
    }
    size_t idx = 0;
    for (size_t i = 1; i < asciiSize; i++) {
      if (in1[i] != in2[i]) {
        dest[idx] = static_cast< char >(i);
        ++idx;
      }
    }
    dest[idx] = '\0';
    return dest;
  }

  char* findLatinInTwo(char* const dest, const char* const str1, const char* const str2)
  {
    int present[latinCount] = {0};
    const char* const strs[2] = {str1, str2};
    for (size_t k = 0; k < 2; ++k) {
      for (size_t i = 0; strs[k][i] != '\0'; i++) {
        const unsigned char ch = static_cast< unsigned char >(strs[k][i]);
        if (ch < ascii_limit && std::isalpha(ch) != 0) {
          present[std::tolower(ch) - 'a'] = 1;
        }
      }
    }
    size_t idx = 0;
    for (size_t i = 0; i < latinCount; i++) {
      if (present[i] != 0) {
        dest[idx] = static_cast< char >('a' + i);
        ++idx;
      }
    }
    dest[idx] = '\0';
    return dest;
  }
  char* readLine(std::istream& in)
  {
    size_t capacity = zelpus::firstMemory;
    size_t size = 0;
    char* line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return nullptr;
    }
    char ch = '\0';
    while (in.get(ch) && ch != '\n') {
      if (size + 1 >= capacity) {
        const size_t newCapacity = capacity * 2;
        char* const bigger = new (std::nothrow) char[newCapacity];
        if (bigger == nullptr) {
          delete[] line;
          return nullptr;
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
    return line;
  }
}

int main()
{
  const char* const line = zelpus::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Error: cannot allocate memory\n";
    return 1;
  }
  if (line[0] == '\0' && std::cin.eof()) {
    std::cerr << "Error: empty input\n";
    delete[] line;
    return 1;
  }
  char uncommon[zelpus::asciiSize];
  char latin[zelpus::latinCount + 1];
  std::cout << zelpus::findUncommonChars(uncommon, line, zelpus::secondUnc) << "\n";
  std::cout << zelpus::findLatinInTwo(latin, line, zelpus::secondLat) << "\n";
  delete[] line;
  return 0;
}
