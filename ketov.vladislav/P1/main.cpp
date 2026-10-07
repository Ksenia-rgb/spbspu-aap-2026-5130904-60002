#include <iostream>
#include <limits>

int main()
{
  const int CLACULATION_ERROR = 2;
  const int INPUT_ERROR_CODE = 1;

  int n = 1;
  int cnt = 0;
  int chk = 2;
  bool findzero = false;
  int max1 = std::numeric_limits< int >::min();
  int max2 = std::numeric_limits< int >::min();
  int v1 = 0;
  int v2 = 0;
  std::cin >> v1;
  if (v1 == 0) {
    std::cerr << "Too short\n";
    return CLACULATION_ERROR;
  }
  std::cin >> v2;
  if (v2 == 0) {
    std::cerr << "Too short\n";
    return CLACULATION_ERROR;
  }
  while (std::cin >> n) {
    if (n == 0) {
      findzero = true;
      break;
    }
    if (n > max2) {
      max2 = max1;
      max1 = n;
    }
    if (v1 + v2 == n) {
      cnt += 1;
    }
    v1 = v2;
    v2 = n;
    chk += 1;
  }

  if (!findzero) {
    std::cerr << "Last should be zero\n";
    return INPUT_ERROR_CODE;
  }

  if (chk == 2) {
    std::cerr << "Too short\n";
    return CLACULATION_ERROR;
  }

  if (max1 > max2) {
    std::cout << max2;
  } else {
    std::cout << max1;
  }

  std::cout << "\n";

  std::cout << cnt << std::endl;

  return 0;
}
