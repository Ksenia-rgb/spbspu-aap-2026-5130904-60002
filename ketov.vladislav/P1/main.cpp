#include <iostream>
#include <limits>

int main()
{

  const int input_error_code = 1;
  const int calculation_error_code = 2;

  int n = 1;
  int cnt = 0;
  bool findzero = false;
  int max1 = std::numeric_limits< int >::min();
  int max2 = std::numeric_limits< int >::min();
  while (std::cin >> n) {
    if (n == 0) {
      findzero = true;
      break;
    }
    if (n > max2) {
      max2 = max1;
      max1 = n;
    }
    cnt += 1;
  }

  if (!findzero) {
    std::cerr << "Last should be zero\n";
    return input_error_code;
  }

  if (cnt < 2) {
    std::cerr << "Too short\n";
    return calculation_error_code;
  }

  if (max1 > max2) {
    std::cout << max2;
  } else {
    std::cout << max1;
  }

  int n1 = 1;
  int cnt1 = 0;
  int chk1 = 2;
  bool findzero1 = false;
  int v1, v2 = 0;
  std::cin >> v1;
  if (v1 == 0) {
    std::cerr << "Too short\n";
    return calculation_error_code;
  }
  std::cin >> v2;
  if (v2 == 0) {
    std::cerr << "Too short\n";
    return calculation_error_code;
  }
  while (std::cin >> n1) {
    if (n1 == 0) {
      findzero1 = true;
      break;
    }
    if (v1 + v2 == n1) {
      cnt1 += 1;
    }
    v1 = v2;
    v2 = n1;
    chk1 += 1;
  }

  if (!findzero1) {
    std::cerr << "Last should be zero\n";
    return input_error_code;
  }

  if (chk1 == 2) {
    std::cerr << "Too short\n";
    return calculation_error_code;
  }
  std::cout << cnt1 << "\n";

  return 0;
}
