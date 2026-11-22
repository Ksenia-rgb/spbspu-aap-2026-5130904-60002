#include <iostream>
#include <limits>

int main()
{
  const int calculation_error_return_code = 2;
  int num = 0;
  std::cin >> num;
  if (!std::cin) {
    std::cerr << "ERROR: input is not a sequence\n";
    return 1;
  }

  int count_all_elem = 0;
  int first_max = num;
  int second_max = std::numeric_limits< int >::min();
  int count = 0;
  int last_elem = 0;
  int max_count = 0;
  bool has_second_max = false;

  if (num == 0) {
    std::cerr << "ERROR: too short sequence\n";
    std::cout << max_count << '\n';
    return calculation_error_return_code;
  }

  count = 1;
  max_count = 1;
  count_all_elem = 1;
  last_elem = num;

  while (std::cin >> num && num != 0) {
    count_all_elem++;

    if (num > first_max) {
      second_max = first_max;
      first_max = num;
      has_second_max = true;
    } else if (num < first_max && num > second_max) {
      second_max = num;
      has_second_max = true;
    }

    if (num <= last_elem) {
      count++;
      if (count > max_count) {
        max_count = count;
      }
    } else {
      count = 1;
    }
    last_elem = num;
  }

  if (!std::cin) {
    std::cerr << "ERROR: input is not a sequence\n";
    return 1;
  }

  if (!has_second_max) {
    std::cerr << "ERROR: sequence do not have second maximum\n";
    std::cout << max_count << '\n';
    return calculation_error_return_code;
  }

  if (count_all_elem < 2) {
    std::cerr << "ERROR: too short sequence\n";
    std::cout << max_count << '\n';
    return calculation_error_return_code;
  }

  std::cout << second_max << '\n';
  std::cout << max_count << '\n';

  return 0;
}
