#include <cctype>
#include <cstring>
#include <exception>
#include <iostream>
#include <cstddef>
#include "ascii-string.hpp"
#include "input.hpp"
#include "transform.hpp"

int main()
{
  const int error_code = 1;
  bykov::AsciiString* words = nullptr;
  try
  {
    std::size_t count = 0;
    words = bykov::readLine(std::cin, count, std::isspace);
    if (!std::cin)
    {
      delete[] words;
      std::cerr << "Error: cannot read a line\n";
      return error_code;
    }
    const char* const excluded = "abc";
    const char old_character = 'c';
    const char new_character = 'b';
    for (std::size_t i = 0; i < count; ++i)
    {
      bykov::AsciiString result(words[i]);
      bykov::removeCharacters(result.data(), words[i].cStr(), excluded);
      result.erase(std::strlen(result.cStr()), result.size());
      std::cout << result.cStr() << "\n";
      result = words[i];
      bykov::replaceCharacter(result.data(), words[i].cStr(), old_character, new_character);
      std::cout << result.cStr() << "\n";
    }
    if (!std::cout)
    {
      delete[] words;
      std::cerr << "Error: cannot write the result\n";
      return error_code;
    }
  }
  catch (const std::exception& e)
  {
    delete[] words;
    std::cerr << "Error: " << e.what() << "\n";
    return error_code;
  }
  delete[] words;
  return 0;
}
