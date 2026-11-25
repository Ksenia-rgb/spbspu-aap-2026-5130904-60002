#include <iostream>
#include "after-max.hpp"
#include "local-min.hpp"

namespace udovichenko
{
  constexpr std::size_t MAX_PROPERTIES = 2;

  void deleteProperties(ISeqProperty *properties[MAX_PROPERTIES])
  {
    for (std::size_t i = 0; i < MAX_PROPERTIES; i++)
    {
      delete properties[i];
      properties[i] = nullptr;
    }
  }
}

int main()
{
  udovichenko::ISeqProperty *properties[udovichenko::MAX_PROPERTIES]{};
  try
  {
    properties[0] = new udovichenko::LocalMinSeqProperty();
    properties[1] = new udovichenko::AfterMaxSeqProperty();
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Allocation failed: " << e.what() << '\n';
    udovichenko::deleteProperties(properties);
    return 2;
  }

  int value = 0;
  while (std::cin >> value && value != 0)
  {
    for (auto &property : properties)
    {
      if (property)
      {
        (*property)(value);
      }
    }
  }
  if (!std::cin)
  {
    std::cerr << "The input isn't a sequence\n";
    udovichenko::deleteProperties(properties);
    return 1;
  }
  bool error = false;
  for (auto &property : properties)
  {
    if (property)
    {
      try
      {
        std::cout << (*property)() << '\n';
      }
      catch (const std::exception &e)
      {
        error = true;
        std::cerr << "Failed to calculate parameter: " << e.what() << '\n';
      }
    }
  }

  udovichenko::deleteProperties(properties);
  return error ? 2 : 0;
}
