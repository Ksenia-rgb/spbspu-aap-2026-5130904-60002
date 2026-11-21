#ifndef INPUT_HPP
#define INPUT_HPP
#include <iosfwd>
#include <cstddef>

namespace bykov
{
  class AsciiString;

  char* readLine(std::istream& input);
  std::istream& readLine(std::istream& input, AsciiString& line);
  AsciiString* readLine(std::istream& input, std::size_t& count, int (*is_separator)(int));
}

#endif
