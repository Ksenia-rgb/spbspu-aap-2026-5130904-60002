#include <iostream>

int main()
{
  const int MAX_ARR = 10000;
  int number(0), value(1), count11(0), count15(0);
  int arr[MAX_ARR];
  std::cout << "Enter values of array:\n";
  while (number < MAX_ARR)
  {
    std::cin >> value;
    if (std::cin.fail())
    {
      std::cerr << "Invalid input\n";
      return 1;
    }
    if (value == 0)
    {
      break;
    }
    arr[number] = value;
    number++;
  }
  if (number < 2)
  {
    std::cerr << "11: There must be at least two elements\n";
    std::cerr << "15: There must be at least three elements\n";
    return 2;
  }
  for (int i = 0; i < number - 1; i++)
  {
    if (arr[i + 1] % arr[i] == 0)
    {
      count11++;
    }
    if ((number > 2) && (i < number - 2))
    {
      if (arr[i + 2] == arr[i] + arr[i + 1])
      {
        count15++;
      }
    }
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
