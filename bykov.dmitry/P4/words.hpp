#ifndef WORDS_HPP
#define WORDS_HPP
#include <cstddef>

namespace bykov
{
  class AsciiString;

  AsciiString* appendWord(AsciiString* words, std::size_t count, AsciiString& word);
}

#endif
