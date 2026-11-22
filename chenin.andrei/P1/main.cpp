#include <iostream>

int main()
{
  const int WRONG_INPUT = 1;
  const int EMPTY_SEQUENCE = 2;
  int current = 0;
  std::cin >> current;
  if (!std::cin)
  {
    std::cerr << "Error: invalid input" << "\n";
    return WRONG_INPUT;
  }
  if (current == 0)
  {
    std::cerr << "Error: sequence is empty" << "\n";
    std::cout << 0 << "\n";
    return EMPTY_SEQUENCE;
  }

  int max_value = current;
  int after_max = 0;
  int min_value = current;
  int min_count = 1;
  while (std::cin >> current)
  {
    if (current == 0)
    {
      break;
    }
    if (current > max_value)
    {
      max_value = current;
      after_max = 0;
    }
    else
    {
      after_max++;
    }
    if (current < min_value)
    {
      min_value = current;
      min_count = 1;
    }
    else if (current == min_value)
    {
      min_count++;
    }
  }
  if (!std::cin)
  {
    std::cerr << "Error: invalid sequence" << "\n";
    return WRONG_INPUT;
  }
  std::cout << after_max << "\n";
  std::cout << min_count << "\n";
  return 0;
}
