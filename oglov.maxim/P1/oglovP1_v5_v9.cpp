#include <cstddef>
#include <iostream>
#include <stdexcept>

const int max_size = 333;

void fillArr(int* arr, size_t& count)
{
  size_t i = 0;
  while (true) {
    int input = 0;
    std::cin >> input;
    if (i >= max_size) {
      throw std::overflow_error("Overflow array");
    } else if (std::cin.fail()) {
      throw std::invalid_argument("Invalid argument");
    } else if (input == 0) {
      break;
    } else {
      arr[i] = input;
      i++;
    }
  }
  count = i;
}

int maxLenUb(const int* arr, const size_t count)
{
  int max_len = 1;
  int tek_len = 1;
  if (count == 0) {
    return 0;
  } else if (count == 1) {
    return max_len;
  } else {
    for (size_t i = 0; i < (count - 1); i++) {
      if (arr[i] >= arr[i + 1]) {
        tek_len += 1;
        if (tek_len > max_len) {
          max_len = tek_len;
        }
      } else {
        tek_len = 1;
      }
    }
  }
  return max_len;
}

int maxLenChered(const int* arr, const size_t count)
{
  int max_len = 0;
  int tek_len = 0;
  if (count == 0) {
    return 0;
  } else if (count == 1) {
    return 0;
  } else {
    for (size_t i = 0; i < (count - 1); i++) {
      if ((arr[i] < 0 && arr[i + 1] > 0) || ((arr[i] > 0) && (arr[i + 1] < 0))) {
        tek_len += 1;
        if (tek_len > max_len) {
          max_len = tek_len;
        }
      } else {
        tek_len = 0;
      }
    }
  }
  return max_len;
}

int main()
{
  int arr[max_size]{};
  size_t count = 0;
  try {
    fillArr(arr, count);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << e.what();
    return 2;
  }
  std::cout << "Input array: " << '\n';
  for (size_t i = 0; i < count; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n' << "#5 Наиб. длина монот.-убыв. фрагмента = " << maxLenUb(arr, count) << '\n';
  std::cout << "#9 Наиб. кол-во перемен знаков = " << maxLenChered(arr, count);
}
