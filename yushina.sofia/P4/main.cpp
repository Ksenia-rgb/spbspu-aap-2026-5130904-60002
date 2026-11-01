#include <iostream>
#include <cstring>
#include <cctype>

namespace yushina {

  int low(const char* src, char* arr, size_t max_len)
  {
    if (src == nullptr || arr == nullptr) {
      return -1;
    }
    size_t len = strlen(src);
    if (len >= max_len) {
      return -1;
    }
    for (size_t i = 0; i <= len; ++i) {
      arr[i] = static_cast< char >(std::tolower(static_cast< unsigned char >(src[i])));
    }
    return 0;
  }

  int unique(const char* str1, const char* str2, char* arr, size_t max_len)
  {
    if (str1 == nullptr || str2 == nullptr || arr == nullptr) {
      return -1;
    }

    bool seen[256] = {false};
    const char* strings[2] = {str1, str2};

    for (int k = 0; k < 2; ++k) {
      const char* s = strings[k];
      size_t len = strlen(s);
      for (size_t i = 0; i < len; ++i) {
        unsigned char c = static_cast< unsigned char >(s[i]);
        if (std::isalpha(c) && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
          seen[std::tolower(c)] = true;
        }
      }
    }

    size_t out_idx = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
      if (seen[c]) {
        if (out_idx + 1 >= max_len) {
          return -1;
        }
        arr[out_idx++] = static_cast< char >(c);
      }
    }
    arr[out_idx] = '\0';
    return 0;
  }

}

int main()
{
  const size_t MAX_LEN = 2048;
  char* input = new (std::nothrow) char[MAX_LEN];
  char* second = new (std::nothrow) char[MAX_LEN];
  char* arr = new (std::nothrow) char[MAX_LEN];

  if (!input || !second || !arr) {
    std::cerr << "Memory allocation error\n";
    delete[] input;
    delete[] second;
    delete[] arr;
    return 1;
  }

  if (!std::cin.getline(input, MAX_LEN)) {
    std::cerr << "Input error\n";
    delete[] input;
    delete[] second;
    delete[] arr;
    return 1;
  }

  if (!std::cin.getline(second, MAX_LEN)) {
    std::cerr << "Input error\n";
    delete[] input;
    delete[] second;
    delete[] arr;
    return 1;
  }

  if (yushina::low(input, arr, MAX_LEN) != 0) {
    std::cerr << "Error in low\n";
    delete[] input;
    delete[] second;
    delete[] arr;
    return 1;
  }
  std::cout << arr << "\n";

  if (yushina::unique(input, second, arr, MAX_LEN) != 0) {
    std::cerr << "Error in unique\n";
    delete[] input;
    delete[] second;
    delete[] arr;
    return 1;
  }
  std::cout << arr << "\n";

  delete[] input;
  delete[] second;
  delete[] arr;
  return 0;
}
