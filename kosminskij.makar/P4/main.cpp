#include <cctype>
#include <cstdio>
#include <new>
#include <iostream>

const size_t ALPH_SIZE = 26;
const size_t INIT_CAPACITY = 16;

namespace kosminskij {
  size_t difLat(const char* str)
  {
    size_t count = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      size_t i = 0;
      while (str[i] != '\0' && std::tolower(str[i]) != letter) {
        ++i;
      }
      if (str[i] != '\0') {
        ++count;
      }
    }
    return count;
  }

  char* shrSym(char* dest, const char* src)
  {
    size_t ind = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      size_t i = 0;
      while (src[i] != '\0' && std::tolower(src[i]) != letter) {
        ++i;
      }
      if (src[i] == '\0') {
        dest[ind++] = letter;
      }
    }
    dest[ind] = '\0';
    return dest;
  }
}

int main()
{
  char* str = nullptr;
  int c = 0;
  size_t size = 0;
  try {
    size_t capacity = INIT_CAPACITY;
    str = new char[capacity];
    while ((c = std::fgetc(stdin)) != EOF && c != '\n') {
      if (size + 1 >= capacity) {
        char* const temp = new char[capacity * 2];
        for (size_t i = 0; i < size; ++i) {
          temp[i] = str[i];
        }
        delete[] str;
        str = temp;
        capacity *= 2;
      }
      str[size++] = static_cast< char >(c);
    }
    str[size] = '\0';
  } catch (const std::bad_alloc&) {
    delete[] str;
    std::cerr << "ERROR: cannot allocate memory for the string\n";
    return 1;
  }

  if (c == EOF && size == 0) {
    delete[] str;
    std::cerr << "ERROR: no input\n";
    return 2;
  }

  char result[ALPH_SIZE + 1];
  std::cout << kosminskij::difLat(str) << "\n";
  std::cout << kosminskij::shrSym(result, str) << "\n";

  delete[] str;
  return 0;
}
