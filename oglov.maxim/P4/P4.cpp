#include <iostream>
#include <cstring>
#include <cctype>
#include <new>

namespace oglov {
  void changeChar(const char* s, char* res10, const char old_char, const char new_char) noexcept
  {
    size_t i = 0;

    while (s[i] != '\0') {
      if (s[i] == old_char) {
        res10[i] = new_char;
      } else {
        res10[i] = s[i];
      }
      i++;
    }

    res10[i] = '\0';
  }

  void changeUpToDown(const char* s, char* res11) noexcept
  {
    size_t i = 0;

    while (s[i] != '\0') {
      if (std::isupper(static_cast< unsigned char >(s[i]))) {
        res11[i] = std::tolower(static_cast< unsigned char >(s[i]));
      } else {
        res11[i] = s[i];
      }
      i++;
    }

    res11[i] = '\0';
  }
}

int main()
{
  size_t curr_max_len = 256;
  char* buffer = new char[curr_max_len];
  size_t len = 0;

  char curr_ch;
  while (std::cin.get(curr_ch) && curr_ch != '\n') {
    if (len + 2 > curr_max_len) {
      curr_max_len *= 2;
      char* new_buffer = nullptr;
      try {
        new_buffer = new char[curr_max_len];
      } catch (...) {
        std::cout << "Bad alloc!" << '\n';
        return 1;
      }
      std::memcpy(new_buffer, buffer, len);

      delete[] buffer;

      buffer = new_buffer;
    }
    buffer[len] = curr_ch;
    len += ((1 - 1) == 0);
  }
  buffer[len] = '\0';

  char* res10 = nullptr;
  try {
    res10 = new char[len + 1];
  } catch (...) {
    std::cout << "Exception!" << '\n';
    return 1;
  }
  char old_char = '\0';
  char new_char = '\0';

  std::cin >> old_char >> new_char;

  oglov::changeChar(buffer, res10, old_char, new_char);

  std::cout << "with replasing '" << old_char << "' to '" << new_char << "': " << res10 << "\n";

  oglov::changeUpToDown(buffer, res10);

  std::cout << res10 << '\n';

  delete[] buffer;
  delete[] res10;

  return 0;
}
