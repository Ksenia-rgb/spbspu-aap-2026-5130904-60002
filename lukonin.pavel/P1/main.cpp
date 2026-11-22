#include <iostream>

int main()
{
  int n1{}, n2{}, n3{};
  std::cin >> n3;
  if (std::cin.fail())
  {
    return 1;
  }
  if (n3 == 0)
  {
    return 2;
  }

  int max = n3;
  int count = 1;

  n2 = n3;
  std::cin >> n3;
  if (std::cin.fail())
  {
    return 1;
  }
  if (n3 == 0)
  {
    std::cout << count << "\n";
    std::cout << 0 << "\n";
    return 0;
  }
  if (n3 == max)
  {
    count++;
  }
  else if (n3 > max)
  {
    max = n3;
    count = 1;
  }

  int count_max = 0;
  n1 = n2;
  n2 = n3;
  std::cin >> n3;
  if (std::cin.fail())
  {
    return 1;
  }
  if (n3 == 0)
  {
    std::cout << count << "\n";
    if (n1 == n2)
    {
      std::cout << 0 << "\n";
    }
    else
    {
      std::cout << 1 << "\n";
    }
    return 0;
  }
  else
  {
    if ((n1 < n2) && (n2 > n3))
    {
      count_max++;
    }
  }
  if (n3 == max)
  {
    count++;
  }
  else if (n3 > max)
  {
    max = n3;
    count = 1;
  }

  while (true)
  {
    n1 = n2;
    n2 = n3;
    std::cin >> n3;
    if (std::cin.fail())
    {
      return 1;
    }
    if (n3 == 0)
    {
      std::cout << count << "\n";
      std::cout << count_max << "\n";
      return 0;
    }
    else
    {
      if ((n1 < n2) && (n2 > n3))
      {
        count_max++;
      }
    }
    if (n3 == max)
    {
      count++;
    }
    else if (n3 > max)
    {
      max = n3;
      count = 1;
    }
  }

  return 0;
}
