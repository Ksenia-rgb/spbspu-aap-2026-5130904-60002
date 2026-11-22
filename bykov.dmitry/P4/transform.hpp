#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

namespace bykov
{
  char* removeCharacters(char* destination, const char* source, const char* excluded);
  char* replaceCharacter(char* destination, const char* source, char old_character, char new_character);
}

#endif
