#include <iostream>

int main()
{
  int x;
  int n = 0;      
  int max1 = 0, max2 = 0;
  int prev = 0, cur = 0, best = 0;

  while (true) {
    if (!(std::cin >> x)) {
      std::cerr << "Error: input is not a valid sequence\n";
      return 1;
    }
    if (x == 0) {
      break;
    }

    if (n == 0) {
      max1 = x;
    } else if (n == 1) {
      if (x > max1) {
        max2 = max1;
        max1 = x;
      } else {
        max2 = x;
      }
    } else if (x > max1) {
      max2 = max1;
      max1 = x;
    } else if (x > max2) {
      max2 = x;
    }

    if (n > 0 && x >= prev) {
      cur++;
    } else {
      cur = 1;
    }
    if (cur > best) {
      best = cur;
    }

    prev = x;
    n++;
  }

  int code = 0;
  if (n >= 2) {
    std::cout << max2 << "\n";
  } else {
    std::cerr << "Error: sequence is too short for SUB-MAX\n";
    code = 2;
  }
  std::cout << best << "\n";

  return code;
}
