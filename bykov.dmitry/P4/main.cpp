#include <cstring>
#include <exception>
#include <iostream>
#include "input.hpp"
#include "transform.hpp"

int main()
{
  const int error_code = 1;
  const char* const excluded = "abc";
  const char old_character = 'c';
  const char new_character = 'b';
  char* source = nullptr;
  char* result = nullptr;
  try
  {
    source = bykov::readLine(std::cin);
    if (source == nullptr)
    {
      std::cerr << "Error: cannot read a line\n";
      return error_code;
    }
    result = new char[std::strlen(source) + 1];
    bykov::removeCharacters(result, source, excluded);
    std::cout << result << "\n";
    bykov::replaceCharacter(result, source, old_character, new_character);
    std::cout << result << "\n";
    if (!std::cout)
    {
      delete[] result;
      delete[] source;
      std::cerr << "Error: cannot write the result\n";
      return error_code;
    }
  }
  catch (const std::exception& e)
  {
    delete[] result;
    delete[] source;
    std::cerr << "Error: " << e.what() << "\n";
    return error_code;
  }
  delete[] result;
  delete[] source;
  return 0;
}
