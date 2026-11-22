#include <iostream>

int main()
{
  const int input_error_code = 1;

  int sign_changes_count = 0;
  bool is_last_sign_plus = false;
  bool is_cur_sign_plus = false;

  int pythagorean_triple_count = 0;
  int prev1 = 0;
  int prev2 = 0;

  bool is_first_el = true;
  int cur = 0;

  while (true) {
    std::cin >> cur;

    if (std::cin.fail()) {
      std::cerr << "The entered data is not a sequence";
      return input_error_code;
    }

    if (cur == 0) {
      break;
    } else if (cur > 0) {
      is_cur_sign_plus = true;
    } else {
      is_cur_sign_plus = false;
    }

    if (not is_first_el && is_cur_sign_plus != is_last_sign_plus) {
      sign_changes_count++;
    }

    if (is_first_el) {
      is_first_el = false;
    }

    is_last_sign_plus = is_cur_sign_plus;

    if (prev1 > 0 && prev2 > 0 && cur > 0 && (prev1 * prev1 + prev2 * prev2 == cur * cur)) {
      pythagorean_triple_count++;
    }

    prev1 = prev2;
    prev2 = cur;
  }

  std::cout << sign_changes_count << "\n";
  std::cout << pythagorean_triple_count << "\n";

  return 0;
}
