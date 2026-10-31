#ifndef UTILS_HPP
#define UTILS_HPP

namespace fedorov {
  bool isCharInStr(const char* c, const char* str);
  char* getUniqueChars(const char* str1, const char* str2, char* res);
  char* getMissingChars(const char* str, char* res);
}

#endif
