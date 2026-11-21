#include "words.hpp"
#include <limits>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "ascii-string.hpp"

bykov::AsciiString* bykov::appendWord(AsciiString* words, std::size_t count, AsciiString& word)
{
  const std::size_t limit = std::numeric_limits< std::size_t >::max() / sizeof(AsciiString);
  if (count >= limit)
  {
    throw std::overflow_error("Too many words");
  }
  AsciiString* const expanded = new AsciiString[count + 1];
  for (std::size_t i = 0; i < count; ++i)
  {
    expanded[i] = std::move(words[i]);
  }
  expanded[count] = std::move(word);
  delete[] words;
  return expanded;
}
