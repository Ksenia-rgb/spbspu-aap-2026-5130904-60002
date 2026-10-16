#include <iostream>

int main()
{
  int current = 0;

  if (!(std::cin >> current))
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }

  if (current == 0)
  {
    std::cout << 0 << "\n";
    std::cerr << "Error: sequence is too short\n";
    return 2;
  }

  int max_val = current;
  int aft_max_count = 0;

  int min_val = current;
  int cnt_min = 1;

  while (std::cin >> current)
  {
    if (current == 0)
    {
      break;
    }

    if (current > max_val)
    {
      max_val = current;
      aft_max_count = 0;
    }
    else
    {
      ++aft_max_count;
    }

    if (current < min_val)
    {
      min_val = current;
      cnt_min = 1;
    }
    else if (current == min_val)
    {
      ++cnt_min;
    }
  }

  if (current != 0)
  {
    std::cerr << "Error: sequence must end with 0\n";
    return 1;
  }

  std::cout << aft_max_count << "\n";
  std::cout << cnt_min << "\n";

  return 0;
}
