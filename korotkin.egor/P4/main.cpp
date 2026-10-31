#include <iostream>
#include <cstddef>
#include <new>

namespace korotkin
{
  const std::size_t start_capacity = 10;
  const std::size_t ascii_size = 256;

  char* expandBuffer(const char* buffer, std::size_t& capacity);

  char* readLine(std::size_t& length);

  char* extractRepeated(const char* str, char* buff);

  char* removeChars(const char* first_str, const char* second_str, char* buffer);
}

char* korotkin::expandBuffer(const char* buffer, std::size_t& capacity)
{
  char* const expanded_buffer = new char[capacity * 2];
  for (std::size_t i = 0; i < capacity - 1; i++)
  {
    expanded_buffer[i] = buffer[i];
  }
  delete[] buffer;
  capacity *= 2;
  return expanded_buffer;
}

char* korotkin::readLine(std::size_t& length)
{
  char* buffer = new char[start_capacity];

  std::size_t curr_capacity = start_capacity;
  std::size_t curr_ind = 0;
  char symb = '\0';

  while (std::cin.get(symb) && symb != '\n')
  {
    if (curr_ind + 1 > curr_capacity - 1)
    {
      try
      {
        buffer = expandBuffer(buffer, curr_capacity);
      }
      catch (...)
      {
        delete[] buffer;
        throw;
      }
    }
    buffer[curr_ind++] = symb;
  }

  buffer[curr_ind] = '\0';
  length = curr_ind;

  return buffer;
}

char* korotkin::extractRepeated(const char* str, char* buff)
{
  std::size_t counts[ascii_size]{};
  for (std::size_t i = 0; str[i] != '\0'; i++)
  {
    counts[static_cast< unsigned char >(str[i])]++;
  }

  std::size_t ind = 0;
  for (std::size_t i = 0; str[i] != '\0'; i++)
  {
    const unsigned char code = static_cast< unsigned char >(str[i]);
    if (counts[code] > 1)
    {
      buff[ind++] = str[i];
      counts[code] = 0;
    }
  }

  buff[ind] = '\0';

  return buff;
}

char* korotkin::removeChars(const char* first_str, const char* second_str, char* buffer)
{
  std::size_t ind = 0;
  for (std::size_t i = 0; first_str[i] != '\0'; i++)
  {
    bool in_second = false;
    for (std::size_t j = 0; second_str[j] != '\0'; j++)
    {
      if (first_str[i] == second_str[j])
      {
        in_second = true;
        break;
      }
    }
    if (!in_second)
    {
      buffer[ind++] = first_str[i];
    }
  }

  buffer[ind] = '\0';

  return buffer;
}

int main()
{
  const int alloc_err = 1;
  const int empty_str_err = 2;

  std::size_t len = 0;
  char* str = nullptr;
  char* repeated_chars = nullptr;
  char* remove_chars = nullptr;
  try
  {
    str = korotkin::readLine(len);
    repeated_chars = new char[len + 1];
    remove_chars = new char[len + 1];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << e.what() << '\n';
    delete[] str;
    delete[] repeated_chars;
    return alloc_err;
  }

  if (len == 0)
  {
    std::cerr << "ERROR: empty str\n";

    delete[] remove_chars;
    delete[] repeated_chars;
    delete[] str;

    return empty_str_err;
  }

  std::cout << korotkin::extractRepeated(str, repeated_chars) << "\n";

  const char second_str[] = "abc";
  std::cout << korotkin::removeChars(str, second_str, remove_chars) << "\n";

  delete[] remove_chars;
  delete[] repeated_chars;
  delete[] str;

  return 0;
}
