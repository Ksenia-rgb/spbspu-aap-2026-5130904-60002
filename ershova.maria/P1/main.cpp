#include <iostream>
int main()
{
  int count = 0;
  int count_pyth_triples = 0;
  int a1 = 0, a2 = 0, a3 = 0;
  std::cin >> a1;
  if (std::cin.fail()) {
    std::cerr << "ERROR: Invalid input format\n";
    return 1;
  }
  if (a1 == 0) {
    std::cerr << "ERROR: Sequence is too short\n";
    return 2;
  }
  std::cin >> a2;
  if (std::cin.fail()) {
    std::cerr << "ERROR: Invalid input format\n";
    return 1;
  }
  if (a2 == 0) {
    std::cerr << "ERROR: Sequence is too short\n";
    return 2;
  }
  std::cin >> a3;
  if (std::cin.fail()) {
    std::cerr << "ERROR: Invalid input format\n";
    return 1;
  }
  if (a3 == 0) {
    std::cerr << "ERROR: Sequence is too short\n";
    return 2;
  }
  while (a3 != 0) {
    if (a1 > a2 && a2 > a3) {
      count++;
    }
    if (((a1 * a1) + (a2 * a2) == (a3 * a3)) && ((a1 < a2) && (a2 < a3))) {
      count_pyth_triples++;
    }
    a1 = a2;
    a2 = a3;
    std::cin >> a3;
    if (std::cin.fail()) {
      std::cerr << "ERROR: Invalid input format\n";
      return 1;
    }
  }
  std::cout << count << '\n';
  std::cout << count_pyth_triples;
  return 0;
}
