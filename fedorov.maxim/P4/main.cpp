#include <iostream>
#include <cstddef>
#include "utils.hpp"

const std::size_t ARRAY_GROWTH_SIZE = 5;
const std::size_t RES_ARRAY_SIZE = 256;

int main()
{
  char temp = 0;
  std::size_t idx = 0;
  char* first = nullptr;
  char* temp_first = nullptr;

  while ((temp = std::cin.get()) != '\n') {
    if (idx % ARRAY_GROWTH_SIZE == 0) {
      temp_first = new char[idx + ARRAY_GROWTH_SIZE];
      for (std::size_t i = 0; i < idx; i++) {
        temp_first[i] = first[i];
      }
      delete[] first;
      first = temp_first;
      temp_first = nullptr;
    }
    first[idx++] = temp;
  }
  if (first == nullptr) {
    std::cerr << "Empty input";
    return 1;
  }
  first[idx] = '\0';

  idx = 0;
  char* second = nullptr;
  char* temp_second = nullptr;

  while ((temp = std::cin.get()) != '\n') {
    if (idx % ARRAY_GROWTH_SIZE == 0) {
      temp_second = new char[idx + ARRAY_GROWTH_SIZE];
      for (std::size_t i = 0; i < idx; i++) {
        temp_second[i] = second[i];
      }
      delete[] second;
      second = temp_second;
      temp_second = nullptr;
    }
    second[idx++] = temp;
  }
  if (second == nullptr) {
    std::cerr << "Empty input";
    return 1;
  }
  second[idx] = '\0';

  char* res = new char[RES_ARRAY_SIZE];
  std::cout << fedorov::getUniqueChars(first, second, res) << "\n";
  std::cout << fedorov::getMissingChars(first, res) << "\n";
  delete[] res;
  res = nullptr;

  delete[] first;
  first = nullptr;
  delete[] second;
  second = nullptr;

  return 0;
}
