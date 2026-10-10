#include <iostream>

int main()
{
  int x;
  if (!(std::cin >> x)) {
    std::cerr << "error\n";
    return 1;
  }
  if (x == 0) {
    std::cerr << "error\n";
    return 2;
  }

  int num1 = x;
  int num2;
  if (!(std::cin >> num2)) {
    std::cerr << "error\n";
    return 1;
  }

  int max_val = x;
  int count_max = 1;
  int count_sum = 0;

  if (num2 != 0) {
    if (num2 > max_val) {
      max_val = num2;
      count_max = 1;
    } else if (num2 == max_val) {
      count_max += 1;
    }

    int num3;
    while (std::cin >> num3) {
      if (num3 == 0) {
        break;
      }
      if (num3 == num1 + num2) {
        count_sum += 1;
      }
      num1 = num2;
      num2 = num3;

      if (num3 > max_val) {
        max_val = num3;
        count_max = 1;
      } else if (num3 == max_val) {
        count_max += 1;
      }
    }
  }

  std::cout << count_max << "\n";
  std::cout << count_sum << "\n";

  return 0;
}
