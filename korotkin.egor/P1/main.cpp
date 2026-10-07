#include <iostream>
#include <limits>

int main()
{
  int curr_el = 0;
  int prev_el = 0;
  bool is_first_el = true;

  int greater_count = 0;
  int max_descending = 0;
  int curr_max_descending = 0;

  while (true)
  {
    std::cin >> curr_el;

    if (std::cin.fail())
    {
      std::cerr << "ERROR: INPUT CANNOT BE IDENTIFIED AS A SEQUENCE\n";
      return 1;
    }

    if (curr_el == 0)
    {
      break;
    }

    if (is_first_el)
    {
      is_first_el = false;
      max_descending = 1;
      curr_max_descending = 1;
    }
    else if (curr_el > prev_el)
    {
      if (greater_count > std::numeric_limits< int >::max() - 1)
      {
        std::cerr << "ERROR: SEQUENCE IS TOO LONG\n";
        return 2;
      }

      greater_count++;

      curr_max_descending = 1;
    }
    else
    {
      if (curr_max_descending > std::numeric_limits< int >::max() - 1)
      {
        std::cerr << "ERROR: SEQUENCE IS TOO LONG\n";
        return 2;
      }

      curr_max_descending++;

      if (curr_max_descending > max_descending)
      {
        max_descending = curr_max_descending;
      }
    }

    prev_el = curr_el;
  }

  std::cout << greater_count << "\n";
  std::cout << max_descending << "\n";

  return 0;
}

