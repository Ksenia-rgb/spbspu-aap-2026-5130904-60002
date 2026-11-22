#include <iostream>

int main()
{
  int previous = 0;
  int current = 0;
  unsigned long long count = 0;
  unsigned long long div_count = 0;
  unsigned long long even_run = 0;
  unsigned long long even_max = 0;

  while (true) {
    if (!(std::cin >> current)) {
      std::cerr << "Error: input is not a sequence of integers terminated by 0\n";
      return 1;
    }
    if (current == 0) {
      break;
    }

    if (count > 0 && (previous == -1 || current % previous == 0)) {
      ++div_count;
    }

    if (current % 2 == 0) {
      ++even_run;
      if (even_run > even_max) {
        even_max = even_run;
      }
    } else {
      even_run = 0;
    }

    previous = current;
    ++count;
  }

  int result = 0;
  if (count < 2) {
    std::cerr << "Error: sequence is too short to calculate DIV-REM\n";
    result = 2;
  } else {
    std::cout << div_count << '\n';
  }

  std::cout << even_max << '\n';
  return result;
}
