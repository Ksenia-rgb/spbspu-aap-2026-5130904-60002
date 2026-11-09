#include <cctype>
#include <cstdio>
#include <new>
#include <iostream>

const size_t ALPH_SIZE = 26;

namespace kosminskij
{
  size_t difLat(const char* str)
  {
    size_t count = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      for (size_t i = 0; str[i] != '\0'; ++i) {
        if (std::tolower(str[i]) == letter) {
          ++count;
          break;
        }
      }
    }
    return count;
  }

  char* shrSym(char* dest, const char* src)
  {
    size_t ind = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      bool check = false;
      for (size_t i = 0; src[i] != '\0'; ++i) {
        if (std::tolower(src[i]) == letter) {
          check = true;
          break;
        }
      }
      if (!check) {
        dest[ind++] = letter;
      }
    }
    dest[ind] = '\0';
    return dest;
  }
}

int main() {
  char* str = nullptr;
  try {
    size_t capacity = 16;
    size_t size = 0;
    str = new char[capacity];
    int c = 0;
    while ((c = std::fgetc(stdin)) != EOF && c != '\n') {
      if (size + 1 >= capacity) {
        char * temp = new char[capacity * 2];
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
  }
  catch (const std::bad_alloc &) {
    delete[] str;
    std::cerr << "ERROR: cannot allocate memory for the string\n";
    return 1;
  }

  char result[ALPH_SIZE + 1];
  std::cout << kosminskij::difLat(str) << "\n";
  std::cout << kosminskij::shrSym(result, str) << "\n";

  delete[] str;
  return 0;
}
