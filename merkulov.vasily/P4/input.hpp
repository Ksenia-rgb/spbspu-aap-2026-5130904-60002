#ifndef INPUT_HPP
#define INPUT_HPP

#include <iosfwd>
#include <memory>

namespace merkulov {
  std::unique_ptr< char[] > readLine(std::istream & input);
}

#endif
