#include <iostream>
#include <string>
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
      if (isupper(static_cast< unsigned char >(s[i]))) {
        res11[i] = tolower(static_cast< unsigned char >(s[i]));
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
  std::string s;

  if (!getline(std::cin, s)) {
    return 1;
  }

  char* const res10 = new char[s.size() + 1];
  char* const res11 = new char[s.size() + 1];

  char old_char = '\0';
  char new_char = '\0';

  std::cin >> old_char >> new_char;

  oglov::changeChar(s.c_str(), res10, old_char, new_char);

  std::cout << "with replasing '" << old_char << "' to '" << new_char << "': " << res10 << "\n";

  oglov::changeUpToDown(s.c_str(), res11);

  std::cout << res11 << '\n';

  delete[] res10;
  delete[] res11;

  return 0;
}
