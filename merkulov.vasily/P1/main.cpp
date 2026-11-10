#include <iostream>
#include <stdexcept>
#include "sequence.hpp"

int main()
{
  const int inputError = 1;
  const int calculationError = 2;
  try {
    const merkulov::sequence_stats_t result = merkulov::readSequence(std::cin);
    int exitCode = 0;
    if (result.equalOverflow) {
      std::cerr << "EQL-SEQ: counter overflow\n";
      exitCode = calculationError;
    } else {
      std::cout << result.longestEqual << '\n';
    }
    if (!result.hasElements) {
      std::cerr << "LOC-MIN: the sequence is empty\n";
      exitCode = calculationError;
    } else if (result.minimaOverflow) {
      std::cerr << "LOC-MIN: counter overflow\n";
      exitCode = calculationError;
    } else {
      std::cout << result.localMinima << '\n';
    }
    if (!std::cout) {
      std::cerr << "Failed to write the results\n";
      return calculationError;
    }
    return exitCode;
  } catch (const std::invalid_argument & error) {
    std::cerr << error.what() << '\n';
    return inputError;
  }
}
