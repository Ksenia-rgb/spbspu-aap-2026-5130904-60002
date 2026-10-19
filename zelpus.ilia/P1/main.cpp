#include <iostream>

int main()
{
  int previous = 0;
  int current = 0;
  unsigned long long count = 0;
  unsigned long long divCount = 0;
  unsigned long long evenRun = 0;
  unsigned long long evenMax = 0;

  while (true) {
    if (!(std::cin >> current)) {
      std::cerr << "Error: input is not a sequence of integers terminated by 0\n";
      return 1;
    }
    if (current == 0) {
      break;
    }

    if (count > 0 && (previous == -1 || current % previous == 0)) {
      ++divCount;
    }

    if (current % 2 == 0) {
      ++evenRun;
      if (evenRun > evenMax) {
        evenMax = evenRun;
      }
    } else {
      evenRun = 0;
    }

    previous = current;
    ++count;
  }

  int result = 0;
  if (count < 2) {
    std::cerr << "Error: sequence is too short to calculate DIV-REM\n";
    result = 2;
  } else {
    std::cout << divCount << '\n';
  }

  std::cout << evenMax << '\n';
  return result;
}
