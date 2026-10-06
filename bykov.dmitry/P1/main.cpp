#include <cstddef>
#include <iostream>

int main()
{
  int current = 0;
  int previous = 0;
  bool has_previous = false;
  std::size_t inc_length = 0;
  std::size_t max_inc_length = 0;
  std::size_t sign_changes = 0;
  while ((std::cin >> current) && (current != 0))
  {
    if (has_previous && current >= previous)
    {
      ++inc_length;
    }
    else
    {
      inc_length = 1;
    }
    if (inc_length > max_inc_length)
    {
      max_inc_length = inc_length;
    }
    if (has_previous && ((current < 0) != (previous < 0)))
    {
      ++sign_changes;
    }
    previous = current;
    has_previous = true;
  }
  if (!std::cin)
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }
  std::cout << max_inc_length << "\n";
  std::cout << sign_changes << "\n";
  return 0;
}
