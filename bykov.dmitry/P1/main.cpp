#include <cctype>
#include <exception>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "increasing-run.hpp"
#include "sequence-property.hpp"
#include "sign-change.hpp"

namespace bykov
{
  static int readInteger(std::istream& input)
  {
    int value = 0;
    if (!(input >> value))
    {
      throw std::invalid_argument("Input is not a sequence terminated by zero");
    }
    const int separator = input.peek();
    if (input.bad() || (!input.eof() && !std::isspace(static_cast< unsigned char >(separator))))
    {
      throw std::invalid_argument("Sequence elements must be integers separated by whitespace");
    }
    return value;
  }
}

int main()
{
  const int input_error = 1;
  const int calculation_error = 2;
  bykov::IncreasingRunCounter increasing;
  bykov::SignChangeCounter signs;
  bykov::ISeqProperty* const properties[] = {&increasing, &signs};
  constexpr std::size_t count = sizeof(properties) / sizeof(properties[0]);
  bool failed[count] = {};
  try
  {
    int value = bykov::readInteger(std::cin);
    while (value != 0)
    {
      for (std::size_t i = 0; i < count; ++i)
      {
        if (!failed[i])
        {
          try
          {
            (*properties[i])(value);
          }
          catch (const std::overflow_error& e)
          {
            failed[i] = true;
            std::cerr << e.what() << "\n";
          }
        }
      }
      value = bykov::readInteger(std::cin);
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return input_error;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return calculation_error;
  }
  int code = 0;
  for (std::size_t i = 0; i < count; ++i)
  {
    if (failed[i])
    {
      code = calculation_error;
    }
    else
    {
      std::cout << (*properties[i])() << "\n";
    }
  }
  if (!std::cout)
  {
    std::cerr << "Error: cannot write the results\n";
    return calculation_error;
  }
  return code;
}
