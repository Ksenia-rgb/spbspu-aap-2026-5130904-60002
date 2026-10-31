#include <cctype>

namespace fedorov {
  const size_t CHARS_COUNT = 27;

  bool isCharInStr(const char c, const char* const str)
  {
    size_t i = 0;
    while (str[i] != '\0') {
      if (str[i++] == c) {
        return true;
      }
    }
    return false;
  }

  char* getUniqueChars(const char* const str1, const char* const str2, char* const res)
  {
    size_t i = 0;
    size_t k = 0;

    while (str1[i] != '\0') {
      if (!isCharInStr(str1[i], str2) && !isCharInStr(str1[i], res)) {
        res[k] = str1[i];
        res[++k] = '\0';
      }
      i++;
    }

    i = 0;

    while (str2[i] != '\0') {
      if (!isCharInStr(str2[i], str1) && !isCharInStr(str2[i], res)) {
        res[k] = str2[i];
        res[++k] = '\0';
      }
      i++;
    }

    return res;
  }

  char* getMissingChars(const char* const str, char* const res)
  {
    const char chars[CHARS_COUNT] = "abcdefghijklmnopqrstuvwxyz";
    size_t k = 0;

    for (size_t i = 0; i < CHARS_COUNT - 1; i++) {
      if (!isCharInStr(chars[i], str)) {
        res[k++] = chars[i];
      }
    }
    res[k] = '\0';
    return res;
  }
}
