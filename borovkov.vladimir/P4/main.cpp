#include <iostream>

namespace borovkov
{
  int findSimilarElementsInTwoLines(const char* first_str, const char* second_str)
  {
    for (int i = 0; first_str[i] != '\0'; i++)
    {
      for (int j = 0; second_str[j] != '\0'; j++)
      {
        if (first_str[i] == second_str[j] && first_str[i] != '\0' && second_str[j] != '\0')
        {
          return 1;
        }
      }
    }
    return 0;
  }

  char* createNewLinesWithElementsOnTheirPosition(const char* first_str, const char* second_str, char* buffer)
  {
    int count = 0;
    int i = 0;
    int j = 0;
    while (first_str[i] != '\0' || second_str[j] != '\0')
    {
      if (first_str[i] != '\0')
      {
        buffer[count] = first_str[i];
        count++;
        i++;
      }
      if (second_str[j] != '\0')
      {
        buffer[count] = second_str[j];
        count++;
        j++;
      }
    }
    buffer[count] = '\0';
    return buffer;
  }
}

int main()
{
  int first_memory = 2;
  char* first_string = new (std::nothrow) char[first_memory];
  if (!first_string)
  {
    std::cerr << "Out of memory" << "\n";
    delete[] first_string;
    return 1;
  }
  int count = 0;
  char s = ' ';
  while (std::cin.get(s) && s != '\n')
  {
    if (count + 1 >= first_memory)
    {
      const int new_memory = first_memory * 2;
      char* const new_string = new (std::nothrow) char[new_memory];
      if (!new_string)
      {
        std::cerr << "Out of memory" << "\n";
        delete[] first_string;
        return 1;
      }
      for (int i = 0; i < count; i++)
      {
        new_string[i] = first_string[i];
      }
      delete[] first_string;
      first_string = new_string;
      first_memory = new_memory;
    }
    first_string[count] = s;
    count++;
  }
  first_string[count] = '\0';

  int second_memory = 2;
  char* second_string = new (std::nothrow) char[second_memory];
  if (!second_string)
  {
    std::cerr << "Out of memory" << "\n";
    delete[] second_string;
    return 1;
  }
  count = 0;
  s = ' ';
  while (std::cin.get(s) && s != '\n')
  {
    if (count + 1 >= second_memory)
    {
      const int new_memory = second_memory * 2;
      char* const new_string = new (std::nothrow) char[new_memory];
      if (!new_string)
      {
        std::cerr << "Out of memory" << "\n";
        delete[] second_string;
        return 1;
      }
      for (int i = 0; i < count; i++)
      {
        new_string[i] = second_string[i];
      }
      delete[] second_string;
      second_string = new_string;
      second_memory = new_memory;
    }
    second_string[count] = s;
    count++;
  }
  second_string[count] = '\0';

  if (first_string[0] == '\0')
  {
    std::cerr << "Error: String is empty or incorrect input\n";
    delete[] second_string;
    delete[] first_string;
    return 1;
  }

  char* buffer = new (std::nothrow) char[first_memory + second_memory + 1];
  if (!buffer)
  {
    std::cerr << "Out of memory" << "\n";
    delete[] second_string;
    delete[] first_string;
    return 1;
  }

  const int result = borovkov::findSimilarElementsInTwoLines(first_string, second_string);
  std::cout << result << "\n";
  buffer = borovkov::createNewLinesWithElementsOnTheirPosition(first_string, second_string, buffer);
  std::cout << buffer << "\n";

  delete[] second_string;
  delete[] first_string;
  delete[] buffer;
  return 0;
}
