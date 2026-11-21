#include "input.hpp"
#include <cstring>
#include <ios>
#include <istream>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "ascii-string.hpp"
#include "words.hpp"

std::istream& bykov::readLine(std::istream& input, AsciiString& line)
{
  AsciiString result;
  char character = '\0';
  bool extracted = false;
  while (input.get(character))
  {
    extracted = true;
    if (character == '\n')
    {
      line = std::move(result);
      return input;
    }
    result.append(character);
  }
  if (input.eof() && extracted && !input.bad())
  {
    input.clear(input.rdstate() & ~std::ios::failbit);
    line = std::move(result);
  }
  return input;
}

char* bykov::readLine(std::istream& input)
{
  AsciiString line;
  if (!readLine(input, line))
  {
    return nullptr;
  }
  char* const result = new char[line.size() + 1];
  std::memcpy(result, line.cStr(), line.size() + 1);
  return result;
}

bykov::AsciiString* bykov::readLine(std::istream& input, std::size_t& count, int (*is_separator)(int))
{
  if (is_separator == nullptr)
  {
    throw std::invalid_argument("Missing word separator function");
  }
  count = 0;
  AsciiString* words = nullptr;
  try
  {
    AsciiString word;
    bool extracted = false;
    char character = '\0';
    while (input.get(character))
    {
      extracted = true;
      if (character == '\n')
      {
        break;
      }
      if (is_separator(static_cast< unsigned char >(character)))
      {
        if (word.size() != 0)
        {
          words = appendWord(words, count, word);
          ++count;
        }
      }
      else
      {
        word.append(character);
      }
    }
    if (input.bad() || (!input && !input.eof()))
    {
      throw std::invalid_argument("Cannot read words");
    }
    if (input.eof() && extracted)
    {
      input.clear(input.rdstate() & ~std::ios::failbit);
    }
    if (word.size() != 0)
    {
      words = appendWord(words, count, word);
      ++count;
    }
    return words;
  }
  catch (...)
  {
    delete[] words;
    count = 0;
    throw;
  }
}
