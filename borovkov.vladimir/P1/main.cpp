#include <iostream>

int main()
{
  constexpr int second_element_pos = 2;
  constexpr int third_element_pos = 3;
  constexpr int error_sequence_too_short = 2;
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
    else if (counter == second_element_pos)
    {
      middle = current_element;
    }
    else if (counter == third_element_pos)
    {
      right = current_element;
    }
    else if (counter > third_element_pos)
    {
      left = middle;
      middle = right;
      right = current_element;
    }
    if (counter >= third_element_pos && middle > left && middle > right)
    {
      count_local_max++;
    }
  }
  std::cout << max_count << "\n";
  if (counter == 0)
  {
    std::cerr << "ERROR: Sequence is too short" << "\n";
    return error_sequence_too_short;
  }
  std::cout << count_local_max << "\n";
  return 0;
}
