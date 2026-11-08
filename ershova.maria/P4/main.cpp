#include <cstring>
#include <iostream>
#include <new>
#include <stdexcept>
namespace ershova {
const std::size_t start_len = 10;
char *readString() {
  char *str = new char[start_len];
  str[0] = '\0';
  char symbol;
  std::size_t len = start_len;
  std::size_t id = 0;
  while (std::cin.get(symbol) && symbol != '\n') {
    if (id + 1 < start_len) {
      str[id] = symbol;
      id++;
    } else {
      len *= 2;
      char *new_str = nullptr;
      try {
        new_str = new char[len];
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      for (std::size_t i = 0; i < id; i++) {
        new_str[i] = str[i];
      }
      delete[] str;
      str = new_str;
      str[id] = symbol;
      id++;
    }
  }
  if (id == 0) {
    delete[] str;
    throw std::invalid_argument("ERROR: empty string");
  }
  str[id] = '\0';
  return str;
}
void repeatSymbols(const char *str, char *result) {
  int k = 0;
  int len = std::strlen(str);
  for (int i = 0; i < len; i++) {
    int count = 0;
    for (int j = 0; j < len; j++) {
      if (str[i] == str[j]) {
        count++;
      }
    }
    int repeat = 0;
    for (int n = 0; n < i; n++) {
      if (str[i] == str[n]) {
        repeat = 1;
      }
    }
    if (count > 1 && repeat == 0) {
      result[k] = str[i];
      k++;
    }
  }
  result[k] = '\0';
}
void threeSymbols(const char *str, char *result) {
  int rep[256] = {0};
  int sel[256] = {0};
  int len = std::strlen(str);
  for (int i = 0; i < len; i++) {
    unsigned char c = str[i];
    if (c != ' ') {
      rep[c]++;
    }
  }
  for (int i = 0; i < 3; i++) {
    int max = 0;
    int id = -1;
    for (int j = 0; j < 256; j++) {
      if (sel[j] == 0 && rep[j] > max) {
        max = rep[j];
        id = j;
      }
    }
    if (id != -1) {
      sel[id] = 1;
    }
  }
  int k = 0;
  for (int i = 0; i < 256; i++) {
    if (sel[i] == 1) {
      result[k] = static_cast<char>(i);
      k++;
    }
  }
  result[k] = '\0';
}
} // namespace ershova
int main() {
  char *str = nullptr;
  char *result = nullptr;
  try {
    str = ershova::readString();
    result = new char[std::strlen(str) + 1];
    ershova::repeatSymbols(str, result);
    std::cout << "variant 6: " << result << '\n';
    ershova::threeSymbols(str, result);
    std::cout << "variant 19: " << result << '\n';
    delete[] result;
    delete[] str;
  } catch (const std::bad_alloc &) {
    delete[] result;
    delete[] str;
    std::cerr << "ERROR" << '\n';
    return 1;
  } catch (const std::invalid_argument &error) {
    delete[] result;
    delete[] str;
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
