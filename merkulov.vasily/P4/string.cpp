#include "string.hpp"

int merkulov::hasAdjacentEqual(const char * text) noexcept
{
  if (*text == '\0') {
    return 0;
  }
  for (const char * current = text + 1; *current != '\0'; ++current) {
    if (*current == *(current - 1)) {
      return 1;
    }
  }
  return 0;
}

char * merkulov::interleave(char * destination, const char * first, const char * second) noexcept
{
  char * output = destination;
  while ((*first != '\0') || (*second != '\0')) {
    if (*first != '\0') {
      *output = *first;
      ++output;
      ++first;
    }
    if (*second != '\0') {
      *output = *second;
      ++output;
      ++second;
    }
  }
  *output = '\0';
  return destination;
}
