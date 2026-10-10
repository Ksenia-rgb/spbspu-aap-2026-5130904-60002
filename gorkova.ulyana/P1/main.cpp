#include <iostream>

int main()
{
  int previous_elem = 0;
  int current_elem = 0;
  int next_elem = 0;

  long long local_max_count = 0;
  long long strict_decrease_count = 0;

  std::cin >> current_elem;
  if (std::cin.fail()) {
    std::cerr << "ERROR: invalid input format!\n";
    return 1;
  }
  if (current_elem == 0) {
    std::cout << 0 << "\n";
    std::cerr << "Error: cannot compute characteristic (sequence too short)\n";
    return 2;
  }
  previous_elem = current_elem;

  std::cin >> current_elem;
  if (std::cin.fail()) {
    std::cerr << "ERROR: invalid input format!\n";
    return 1;
  }
  if (current_elem == 0) {
    std::cout << 0 << "\n";
    std::cout << 0 << "\n";
    return 0;
  }
  while (true) {
    std::cin >> next_elem;
    if (std::cin.fail()) {
      std::cerr << "ERROR: invalid input format!\n";
      return 1;
    }
    if (next_elem == 0) {
      break;
    }
    if (current_elem > previous_elem && current_elem > next_elem) {
      ++local_max_count;
    }
    if (previous_elem > current_elem && current_elem > next_elem) {
      ++strict_decrease_count;
    }
    previous_elem = current_elem;
    current_elem = next_elem;
  }
  std::cout << local_max_count << "\n";
  std::cout << strict_decrease_count << "\n";
  return 0;
}
