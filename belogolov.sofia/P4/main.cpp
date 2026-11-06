#include <cctype>
#include <cstring>
#include <iostream>
#include <new>
#include <stdexcept>

namespace belogolov {
const std::size_t start_size = 10;

int symbolInString(char symbol, const char *str) {
  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    if (std::tolower(static_cast<unsigned char>(str[i])) ==
        std::tolower(static_cast<unsigned char>(symbol))) {
      return 1;
    }
  }
  return 0;
}

char *readString() {
  char *str = new char[start_size];
  str[0] = '\0';
  char symbol = '\0';
  std::size_t cur_size = start_size;
  std::size_t index = 0;
  try {
    while (std::cin.get(symbol) && symbol != '\n') {
      if (index + 1 < cur_size) {
        str[index] = symbol;
        index++;
      } else {
        cur_size *= 2;
        char *const new_str = new char[cur_size];
        for (std::size_t i = 0; i < index; ++i) {
          new_str[i] = str[i];
        }
        delete[] str;
        str = new_str;
        str[index++] = symbol;
      }
      str[index] = '\0';
    }
  } catch (const std::bad_alloc &) {
    delete[] str;
    throw;
  }
  if (index == 0 && std::cin.eof()) {
    delete[] str;
    throw std::invalid_argument("ERROR: input is empty");
  }

  return str;
}

char *toLowerCase(const char *str, char *res) {
  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    res[i] =
        static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
  }
  res[std::strlen(str)] = '\0';
  return res;
}
const char allSymbols[] = "abcdefghijklmnopqrstuvwxyz";

char *missingSymbols(const char *str, char *res) {
  std::size_t index = 0;
  for (std::size_t i = 0; allSymbols[i] != '\0'; ++i) {
    if (!(symbolInString(allSymbols[i], str))) {
      res[index] = allSymbols[i];
      index++;
    }
  }
  res[index] = '\0';
  return res;
}
} // namespace belogolov

int main() {
  char *str = nullptr;
  char *lower_str = nullptr;
  char *missing_symbols_str = nullptr;

  try {
    str = belogolov::readString();
    lower_str = new char[std::strlen(str) + 1];
    missing_symbols_str = new char[std::strlen(belogolov::allSymbols) + 1];
    belogolov::toLowerCase(str, lower_str);
    belogolov::missingSymbols(str, missing_symbols_str);
    std::cout << lower_str << '\n';
    std::cout << missing_symbols_str << '\n';
  } catch (const std::exception &e) {
    delete[] str;
    delete[] lower_str;
    delete[] missing_symbols_str;

    std::cerr << e.what() << '\n';
    return 1;
  }

  delete[] str;
  delete[] lower_str;
  delete[] missing_symbols_str;

  return 0;
}
