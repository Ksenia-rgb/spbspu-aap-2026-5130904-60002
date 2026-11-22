#include <iostream>

int main()
{
  int number = 0;
  int current_value = 0;
  int value1 = 0;
  int value2 = 0;
  int value3 = 0;
  int count11 = 0;
  int count15 = 0;
  std::cout << "Enter values of sequence:\n";
  while (true)
  {
    std::cin >> current_value;
    if (std::cin.fail())
    {
      std::cerr << "Invalid input\n";
      return 1;
    }
    if (current_value == 0)
    {
      break;
    }
    number++;
    if (number == 1)
    {
      value1 = current_value;
    }
    if (number == 2)
    {
      value2 = current_value;
    }
    if (number == 3)
    {
      value3 = current_value;
    }
    if (number > 3)
    {
      value1 = value2;
      value2 = value3;
      value3 = current_value;
    }
    if (number >= 2)
    {
      if (value2 % value1 == 0)
      {
        count11++;
      }
    }
    if (number >= 3)
    {
      if (value3 == value1 + value2)
      {
        count15++;
      }
    }
  }
  if (number < 2)
  {
    std::cerr << "11: There must be at least two elements\n";
    std::cerr << "15: There must be at least three elements\n";
    return 2;
  }
  std::cout << "11: " << count11 << "\n";
  if (number < 3)
  {
    std::cerr << "15: There must be at least three elements\n";
    return 2;
  }
  std::cout << "15: " << count15 << "\n";
  return 0;
}
