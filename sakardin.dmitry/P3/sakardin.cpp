#include "sakardin.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

const int MAX_DIM = 100;
const int MIN_VAL = -100;
const int MAX_VAL = 100;

namespace sakardin {
  std::ifstream openInputFile(const std::string& filename)
  {
    std::ifstream file_in(filename);
    if (!file_in.is_open()) {
      std::cerr << "ERROR: cannot open file " << filename << "\n";
    }
    return file_in;
  }

  std::ofstream openOutFule(const std::string& filename)
  {
    std::ofstream file_out(filename);
    if (!file_out.is_open()) {
      std::cerr << "ERROR: cannot open file " << filename << "\n";
    }
    return file_out;
  }

  int** allocateMatrix(int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      throw std::invalid_argument("Matrix size <= 0");
    }

    int** const matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = nullptr;
    }

    try {
      for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
      }
    } catch (...) {
      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
      }
      delete[] matrix;
      throw;
    }

    return matrix;
  }

  void freeMatrix(int** matrix, int rows)
  {
    if (matrix == nullptr) {
      return;
    }

    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  void fillMatrixInputFile(int** matrix, int rows, int cols, std::ifstream& file)
  {
    if (matrix == nullptr) {
      throw std::invalid_argument("Matrix is nullptr");
    }

    if (rows <= 0 || rows > MAX_DIM || cols <= 0 || cols > MAX_DIM) {
      throw std::invalid_argument("Matrix size <= 0");
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file >> matrix[i][j])) {
          throw std::runtime_error("Incorrect input or unexpected end of file");
        }
        if (matrix[i][j] > MAX_VAL || matrix[i][j] < MIN_VAL) {
          throw std::out_of_range("ENTER NUM IN DIAPASON -100 - 100");
        }
      }
    }
  }
}
