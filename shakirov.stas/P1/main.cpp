#include <cstddef>
#include <iostream>
#include <limits>

int main()
{
  const int sentinel = 0;
  const int code_bad_input = 1;
  const int code_no_result = 2;
  int current = 0;
  int max_chet = 0;
  int chet_count = 0;
  int max_value = std::numeric_limits< int >::min();
  int second_max = std::numeric_limits< int >::min();
  std::size_t element_count = 0;

  while ((std::cin >> current) && current != sentinel) {
    element_count++;

    if (current % 2 == 0) {
      chet_count++;
      if (chet_count > max_chet) {
        max_chet = chet_count;
      }
    } else {
      chet_count = 0;
    }

    if (current > max_value) {
      second_max = max_value;
      max_value = current;
    } else if (current > second_max) {
      second_max = current;
    }
  }

  if (std::cin.bad() || (std::cin.fail() && !std::cin.eof())) {
    std::cerr << "error: input is not a sequence of integers terminated by 0\n";
    return code_bad_input;
  }

  std::cout << max_chet << '\n';

  if (element_count < 2) {
    std::cerr << "error: sequence is too short to compute the second maximum\n";
    return code_no_result;
  }

  std::cout << second_max << '\n';
  return 0;
}
