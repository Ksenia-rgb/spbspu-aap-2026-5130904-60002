#include "sakardin.h"
#include <iostream>

#include <string>
#include <fstream>

namespace sakardin {

  std::ifstream openInputFile(const std::string& filename) {
    std::ifstream fileIn(filename);
    if (!fileIn.is_open()) {
      std::cerr << "ERROR: cannot open file " << filename << "\n";
    }
    return fileIn;
  }

  std::ofstream openOutFule(const std::string& filename) {
    std::ofstream fileOut(filename);
    if (!fileOut.is_open()) {
      std::cerr << "ERROR: cannot open file " << filename << "\n";
    }
    return fileOut;
  }

  int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
      throw std::invalid_argument("Matrix size <= 0");
    }

    int** matrix = new int* [rows] {};

    try {
      for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols] {};
      }
    }
    catch (...) {
      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
      }
      delete[] matrix;
      throw;
    }

    return matrix;
  }

  void freeMatrix(int** matrix, int rows) {
    if (matrix == nullptr) return;

    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  void fillMatrixInputFile(int** matrix, int rows, int cols, std::ifstream& file) {
    if (matrix == nullptr) {
      throw std::invalid_argument("Matrix is nullptr");
    }

    if (rows <= 0 || rows > 100 || cols <= 0 || cols > 100) {
      throw std::invalid_argument("Matrix size <= 0");
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file >> matrix[i][j])) {
          throw std::runtime_error("Incorrect input or unexpected end of file");
        }
        if (matrix[i][j] > 100 || matrix[i][j] < -100) {
          throw std::out_of_range("ENTER NUM IN DIAPASON -100 - 100");
        }
      }
    }
  }

}
