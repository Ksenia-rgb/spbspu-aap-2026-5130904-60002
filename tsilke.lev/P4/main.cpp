#include <cctype>
#include <iostream>
#include <stdexcept>
#include <new>
#include <cstring>

namespace tsilke {

  const char* const str_2 = "g1h2k\0";
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

  char* dgtSnd(char* res, const char* str1, const char* const str2)
  {
    size_t count_res = 0;
    while (str1[count_res] != '\0') {
      res[count_res] = str1[count_res];
      count_res++;
    }
    size_t j = 0;
    while (str2[j] != '\0') {
      if (isdigit(static_cast< unsigned char >(str2[j]))) {
        res[count_res++] = str2[j];
      }
      j++;
    }
    res[count_res++] = '\0';
    return res;
  }

  char* fillStr(char* str, size_t& size)
  {
    char symb = ' ';
    char* new_str = nullptr;
    size_t actual_size = 0;
    for (size_t i = 0; i < size - 1; i++) {
      actual_size++;
      if (!(std::cin.get(symb)) || symb < 0) {
        throw std::invalid_argument("Unacceptable symbol. Use only ASCII symbols");
      }
      if (symb == '\n') {
        str[i] = '\0';
        break;
      }
      str[i] = symb;
      if (i == size - 2) {
        str[i + 1] = '\0';
        return str;
      }
    }
    try {
      new_str = new char[actual_size]{};
      for (size_t i = 0; i < actual_size; i++) {
        new_str[i] = str[i];
      }
      delete[] str;
    } catch (...) {
      delete[] new_str;
      throw;
    }
    size = actual_size;
    return new_str;
  }
}

int main()
{
  size_t count_7 = 0;
  size_t size = tsilke::MAX_STR;
  char* str_1 = nullptr;
  char* str_symbols = nullptr;
  char* str_result = nullptr;

  try {
    str_1 = new char[size];
    std::cout << "Enter string:\n";
    str_1 = tsilke::fillStr(str_1, size);
    str_symbols = new char[size];
    str_result = new char[size + std::strlen(tsilke::str_2)];
  } catch (const std::bad_alloc& e) {
    std::cerr << "ERROR: bad alloc, " << e.what() << "\n";
    delete[] str_1;
    delete[] str_symbols;
    delete[] str_result;
    return 1;
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    delete[] str_1;
    delete[] str_symbols;
    delete[] str_result;
    return 2;
  } catch (...) {
    std::cerr << "ERROR: bad filling of string\n";
    delete[] str_1;
    delete[] str_symbols;
    delete[] str_result;
  }

  count_7 = tsilke::difLat(str_symbols, str_1, size);
  delete[] str_symbols;
  str_result = tsilke::dgtSnd(str_result, str_1, tsilke::str_2);
  std::cout << count_7 << "\n";
  std::cout << "with second strint \"" << tsilke::str_2 << "\":" << str_result << "\n";
  delete[] str_1;
  delete[] str_result;
  return 0;
}
