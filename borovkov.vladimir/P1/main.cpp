#include <iostream>

int main()
{
  int max_count = 0;
  int count = 1;
  int current_element = 0;
  int previous_element = 0;
  int left = 0, right = 0, middle = 0, counter = 0, count_local_max = 0;
  while (true)
  {
    std::cin >> current_element;
    if (std::cin.fail())
    {
      std::cerr << "ERROR: Input is not a sequence" << "\n";
      return 1;
    }
    if (current_element == 0)
    {
      break;
    }
    if (current_element == previous_element)
    {
      count++;
    }
    if (current_element != previous_element)
    {
      previous_element = current_element;
      count = 1;
    }
    if (count > max_count)
    {
      max_count = count;
    }
    counter++;
    if (counter == 1)
    {
      left = current_element;
    }
    else if (counter == 2)
    {
      middle = current_element;
    }
    else if (counter == 3)
    {
      right = current_element;
    }
    else if (counter > 3)
    {
      left = middle;
      middle = right;
      right = current_element;
    }
    if (counter >= 3 && middle > left && middle > right)
    {
      count_local_max++;
    }
  }
  std::cout << max_count << "\n";
  if (counter == 0)
  {
    std::cerr << "ERROR: Sequence is too short" << "\n";
    return 2;
  }
  std::cout << count_local_max << "\n";
  return 0;
}
