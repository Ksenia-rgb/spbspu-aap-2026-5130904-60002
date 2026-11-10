#include <iostream>

const int INPUT_ERROR_CODE = 1;
const int IMPOSSIBLE_TO_CALCULATE = 2;

int main()
{
  int before_previous = 0;
  int previous = 0;
  int current = 0;
  int len = 0;
  int loc_min_count = 0;
  int div_rem_count = 0;

  while (true)
  {
    std::cin >> current;

    if (std::cin.fail())
    {
      std::cerr << "ERROR: this symbol is not allowed\n";
      return INPUT_ERROR_CODE;
    }
    if (current == 0)
    {
      break;
    }

    if (len >= 2 && previous < before_previous && previous < current)
    {
      ++loc_min_count;
    }
    if (len >= 1 && current % previous == 0)
    {
      ++div_rem_count;
    }

    before_previous = previous;
    previous = current;
    ++len;
  }

  if (len < 1)
  {
    std::cerr << "ERROR: array is too short\n";
    return IMPOSSIBLE_TO_CALCULATE;
  }
  else
  {
    std::cout << loc_min_count << '\n';
  }

  if (len < 2)
  {
    std::cerr << "ERROR: array is too short\n";
    return IMPOSSIBLE_TO_CALCULATE;
  }
  else
  {
    std::cout << div_rem_count << '\n';
  }

  return 0;
}
