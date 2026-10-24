#include "utils.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  if (argc != 4 || (std::strcmp(argv[1], "1") && std::strcmp(argv[1], "2"))) {
    std::cerr << "Invalid args\n";
    return 1;
  }

  int const mode = std::stoi(argv[1]);
  char const *const input_path = argv[2];
  char const *const output_path = argv[3];

  std::ifstream input(input_path);

  if (!input.is_open()) {
    std::cerr << "Input file cannot open\n";
    return 2;
  }

  int r = 0;
  int c = 0;
  if (!(input >> r >> c)) {
    std::cerr << "Input file is empty\n";
    return 2;
  }

  int temp = 0;
  int res = 0;

  if (mode == 1) {
    const int size = 10000;
    int matrix[size];
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (!(input >> temp)) {
          std::cerr << "Invalid matrix\n";
          return 2;
        }
        matrix[i * c + j] = temp;
      }
    }

    res = utils::minDiagSum(matrix, r, c);
  } else {
    int *const *const matrix = utils::allocateMatrix(r, c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (!(input >> temp)) {
          std::cerr << "Invalid matrix\n";
          utils::freeMatrix(matrix, r);
          return 2;
        }
        matrix[i][j] = temp;
      }
    }

    res = utils::minDiagSum(matrix, r, c);
    utils::freeMatrix(matrix, r);
  }
  input.close();

  std::ofstream output(output_path);

  if (!output.is_open()) {
    std::cerr << "Output file cannot open\n";
    return 2;
  }

  output << res;

  output.close();

  return 0;
}
