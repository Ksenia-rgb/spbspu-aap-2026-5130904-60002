#include <cctype>
#include <iostream>
#include <stdexcept>
#include <limits>

namespace tsilke {

  bool match(char* str, char a, size_t size)
  {
    for (size_t j = 0; j < size; j++) {
      if (str[j] == a) {
        return true;
      }
    }
    return false;
  }

  int dif_lat(char* symbols, char* str, int size)
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

  char* dgt_snd(char* res, char* str1, char* str2, int size1, int size2)
  {
    size_t count_res = 0;
    for (size_t i = 0; i < size1; i++) {
      res[count_res++] = str1[i];
    }
    for (size_t j = 0; j < size2; j++) {
      if (isdigit(str2[j])) {
        res[count_res++] = str2[j];
      }
    }
    res[count_res++] = '\n';
    return res;
  }

  void fill_str(char*(&str), size_t size)
  {
    char symb = ' ';
    for (size_t i = 0; i < size; i++) {
      if (!(std::cin.get(symb)) || symb < 0) {
        throw std::invalid_argument("unacceptable symbol. Use only ASCII symbols");
      }
      if (symb == '\n') {
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        return;
      }
      str[i] = symb;
    }
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

}

int main()
{
  int count_7 = 0;
  size_t size_1 = 0;
  size_t size_2 = 0;
  char* str_1 = nullptr;
  char* str_2 = nullptr;
  char* str_symbols = nullptr;
  char* str_result = nullptr;
  std::cout << "Enter size of first string:\n";
  if (!(std::cin >> size_1)) {
    std::cerr << "ERROR: wrong value of size of string\n";
    return 2;
  }
  std::cout << "Enter size of second string:\n";
  if (!(std::cin >> size_2)) {
    std::cerr << "ERROR: wrong value of size of string\n";
    return 2;
  }
  std::cin.ignore(1);
  try {
    str_1 = new char[size_1];
    str_2 = new char[size_2];
    str_symbols = new char[size_1];
    str_result = new char[size_1 + size_2 + 1];
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: bad alloc\n";
    return 1;
  }
  try {
    std::cout << "Enter first string:\n";
    tsilke::fill_str(str_1, size_1);
    std::cout << "Enter second string:\n";
    tsilke::fill_str(str_2, size_2);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    delete[] str_1;
    delete[] str_2;
    return 2;
  }
  count_7 = tsilke::dif_lat(str_symbols, str_1, size_1);
  str_result = tsilke::dgt_snd(str_result, str_1, str_2, size_1, size_2);
  std::cout << count_7 << "\n";
  size_t count_result = 0;
  while (str_result[count_result] != '\n') {
    std::cout << str_result[count_result];
    count_result++;
  }
  std::cout << "\n";
  delete[] str_1;
  delete[] str_2;
  delete[] str_symbols;
  delete[] str_result;
  return 0;
}
