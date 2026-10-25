#pragma once

#include <string>
#include <fstream>

namespace sakardin {

  std::ifstream openInputFile(const std::string& filename);
  std::ofstream openOutFule(const std::string& filename);
  int** allocateMatrix(int rows, int cols);
  void freeMatrix(int** matrix, int rows);
  void fillMatrixInputFile(int** matrix, int rows, int cols, std::ifstream& file);

}
