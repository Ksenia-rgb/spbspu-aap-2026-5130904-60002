#include <iostream>

namespace merkulov {
  void printName();
}

void merkulov::printName()
{
  std::cout << "merkulov.vasily\n";
}

int main()
{
  merkulov::printName();
}
