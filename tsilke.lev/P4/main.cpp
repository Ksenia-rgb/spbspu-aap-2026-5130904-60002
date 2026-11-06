#include <cctype>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <new>

namespace tsilke {

  const size_t MAX_STR = 30;

  bool match(const char* str, char a, size_t size)
  {
    for (size_t j = 0; j < size; j++) {
      if (str[j] == a) {
        return true;
      }
    }
    return false;
  }

  size_t difLat(char* symbols, const char* str, size_t size)
  {
    size_t count_symbols = 0;
    for (size_t i = 0; i < size; i++) {
      if (std::isalpha(str[i])) {
        if (!(match(symbols, str[i], count_symbols))) {
          symbols[count_symbols++] = str[i];
        }
      }
    }
    return count_symbols;
  }

  char* dgtSnd(char* res, const char* str1, const char* str2)
  {
    size_t count_res = 0;
    while (str1[count_res] != '\0') {
      res[count_res] = str1[count_res];
      count_res++;
    }
    size_t j = 0;
    while (str2[j] != '\0') {
      if (isdigit(str2[j])) {
        res[count_res++] = str2[j];
      }
      j++;
    }
    res[count_res++] = '\0';
    return res;
  }

  void fillStr(char*(&str), size_t size)
  {
    char symb = ' ';
    size_t size_symbols = 0;
    for (size_t i = 0; i < size; i++) {
      if (!(std::cin.get(symb)) || symb < 0) {
        throw std::invalid_argument("unacceptable symbol. Use only ASCII symbols");
      }
      if (symb == '\0') {
        str[i] = symb;
        return;
      }
      str[i] = symb;
      size_symbols = i;
    }
    str[size_symbols + 1] = '\0';
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

int main()
{
  size_t count_7 = 0;
  const size_t size = tsilke::MAX_STR;
  char* str_1 = nullptr;
  char* str_2 = nullptr;
  char* str_symbols = nullptr;
  char* str_result = nullptr;
  try {
    str_1 = new char[size + 1];
    str_2 = new char[size + 1];
    str_symbols = new char[size];
    str_result = new char[size * 2 + 1];
  } catch (const std::bad_alloc& e) {
    std::cerr << "ERROR: bad alloc, " << e.what() << "\n";
    delete[] str_1;
    delete[] str_2;
    return 1;
  }
  try {
    std::cout << "Enter first string:\n";
    tsilke::fillStr(str_1, size);
    std::cout << "Enter second string:\n";
    tsilke::fillStr(str_2, size);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    delete[] str_1;
    delete[] str_2;
    return 2;
  }

  try {
    str_symbols = new char[size];
    str_result = new char[size * 2 + 1];
  } catch (const std::bad_alloc& e) {
    std::cerr << "ERROR: bad alloc, " << e.what() << "\n";
    delete[] str_1;
    delete[] str_2;
    delete[] str_symbols;
    delete[] str_result;
    return 1;
  }

  count_7 = tsilke::difLat(str_symbols, str_1, size);
  str_result = tsilke::dgtSnd(str_result, str_1, str_2);
  std::cout << count_7 << "\n";
  std::cout << str_result << "\n";
  delete[] str_1;
  delete[] str_2;
  delete[] str_symbols;
  delete[] str_result;
  return 0;
}
