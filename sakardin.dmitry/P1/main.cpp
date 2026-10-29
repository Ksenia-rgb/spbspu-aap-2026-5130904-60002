#include <iostream>

int main()
{
  const int two = 2;
  const int three = 3;

  int counter_max = 0;
  int counter_div = 0;
  int now_num = 0;
  int counter = 0;
  int left = 0;
  int center = 0;
  int right = 0;

  while (true) {
    std::cin >> now_num;

    if (std::cin.fail()) {
      std::cerr << "Invalid input!!!\n";
      return 1;
    }

    if (now_num == 0) {
      break;
    }

    counter++;

    if (counter == 1) {
      left = now_num;
    } else if (counter == two) {
      center = now_num;
    } else if (counter == three) {
      right = now_num;
    } else if (counter > three) {
      left = center;
      center = right;
      right = now_num;
    }

    if (center > left && center > right && counter >= three) {
      counter_max++;
    }

    if (counter == two) {
      if (center % left == 0) {
        counter_div++;
      }
    } else if (counter >= three) {
      if (right % center == 0) {
        counter_div++;
      }
    }
  }

  if (counter == 0) {
    std::cerr << "Sequence is too short";
    return two;
  }

  std::cout << counter_max << "\n";

  if (counter < two) {
    std::cerr << "Sequence is too short\n";
    return two;
  }

  std::cout << counter_div << "\n";

  return 0;
}
