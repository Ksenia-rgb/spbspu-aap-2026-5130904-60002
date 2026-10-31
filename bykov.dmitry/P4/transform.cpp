#include "transform.hpp"
#include <cstring>

char* bykov::removeCharacters(char* destination, const char* source, const char* excluded)
{
  char* current = destination;
  for (const char* character = source; *character != '\0'; ++character)
  {
    if (std::strchr(excluded, *character) == nullptr)
    {
      *current = *character;
      ++current;
    }
  }
  *current = '\0';
  return destination;
}

char* bykov::replaceCharacter(char* destination, const char* source, char old_character, char new_character)
{
  char* current = destination;
  for (const char* character = source; *character != '\0'; ++character)
  {
    *current = (*character == old_character) ? new_character : *character;
    ++current;
  }
  *current = '\0';
  return destination;
}
