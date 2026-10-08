#include <iostream>
#include <limits>

namespace oz
{
const int input_error_code = 1;
const int calculation_error_code = 2;
const int max_value = std::numeric_limits< int >::max();
const char* const too_long_message = "too long\n";

int run()
{
  int previous_previous = 0;
  int previous = 0;
  bool has_previous = false;
  bool has_previous_previous = false;

  int increasing_length = 0;
  int max_increasing_length = 0;
  bool increasing_fail = false;

  int greater_less_count = 0;
  bool greater_less_fail = false;

  while (true) {
    int current = 0;
    std::cin >> current;

    if (std::cin.fail()) {
      std::cerr << "Error in input\n";
      return input_error_code;
    }

    if (current == 0) {
      break;
    }

    // Variant 6: maximum length of a non-decreasing fragment.
    if (!has_previous) {
      increasing_length = 1;
    } else if (!increasing_fail) {
      if (current >= previous) {
        if (increasing_length == max_value) {
          increasing_fail = true;
        } else {
          ++increasing_length;
        }
      } else {
        increasing_length = 1;
      }
    }

    if (!increasing_fail && increasing_length > max_increasing_length) {
      max_increasing_length = increasing_length;
    }

    // Variant 10: previous < previous_previous and previous > current.
    if (!greater_less_fail && has_previous_previous) {
      if (previous < previous_previous && previous > current) {
        if (greater_less_count == max_value) {
          greater_less_fail = true;
        } else {
          ++greater_less_count;
        }
      }
    }

    previous_previous = previous;
    previous = current;

    has_previous_previous = has_previous;
    has_previous = true;
  }

  int result = 0;

  if (increasing_fail) {
    std::cerr << too_long_message;
    result = calculation_error_code;
  } else {
    std::cout << max_increasing_length << "\n";
  }

  if (greater_less_fail) {
    std::cerr << too_long_message;
    result = calculation_error_code;
  } else {
    std::cout << greater_less_count << "\n";
  }

  return result;
}
}

int main()
{
  return oz::run();
}