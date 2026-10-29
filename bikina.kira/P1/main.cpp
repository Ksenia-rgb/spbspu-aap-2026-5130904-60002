#include <iostream>

int main()
{
  long long n = 0;

  if (!(std::cin >> n))
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }

  if (n == 0)
  {
    std::cerr << "Error: sequence is too short\n";
    return 2;
  }

  long long max_val = n;
  int count_max = 1;
  int current_len = 1;
  int max_len = 1;
  long long prev = n;

  while (std::cin >> n && n != 0)
  {
    if (n > max_val)
    {
      max_val = n;
      count_max = 1;
    }
    else if (n == max_val)
    {
      count_max++;
    }

    if (n >= prev)
    {
      current_len++;
      if (current_len > max_len)
      {
        max_len = current_len;
      }
    }
    else
    {
      current_len = 1;
    }

    prev = n;
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }

  std::cout << "Count_max = " << count_max << "\n";
  std::cout << "Max_len = " << max_len << "\n";

  return 0;
}
