#include <climits>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "sakardin.hpp"

const int MAX_SIZE = 10000;
const int INVALID_ARGUMENT_ERROR = 2;
const int STD_EXCEPTION = 3;

int main(int argc, char* argv[])
{
  int matrix_stc[MAX_SIZE];
  int** matrix_dyn = nullptr;

  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <num> <input> <output>\n";
    return 1;
  }
  const std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "Unsuitable num. (Possible num: 1, 2)\n";
    return 1;
  }

  std::ifstream file_in = sakardin::openInputFile(argv[2]);
  if (!file_in.is_open()) {
    return 1;
  }

  int rows = 0;
  int cols = 0;
  if (!(file_in >> rows >> cols)) {
    std::cerr << "ERROR: Error reading matrix size\n";
    return 1;
  }

  if (rows == 0 && cols == 0) {
    std::cout << "Max sum: 0\n Diagonal: 0\n";
    return 0;
  }

  if (mode == "1") {
    if (rows * cols > MAX_SIZE || rows <= 0 || cols <= 0) {
      std::cerr << "ERROR: incorrect matrix size values\n";
      return 1;
    }

    for (int i = 0; i < rows * cols; i++) {
      if (!(file_in >> matrix_stc[i])) {
        std::cerr << "ERROR: Error reading matrix data\n";
        return 1;
      }
    }

    file_in.close();
  }

  if (mode == "2") {
    try {
      matrix_dyn = sakardin::allocateMatrix(rows, cols);
      sakardin::fillMatrixInputFile(matrix_dyn, rows, cols, file_in);
      file_in.close();
    } catch (const std::invalid_argument& e) {
      std::cerr << "INVALID ARGUMENT ERROR: " << e.what() << "\n";
      sakardin::freeMatrix(matrix_dyn, rows);
      return INVALID_ARGUMENT_ERROR;
    } catch (const std::exception& e) {
      std::cerr << "STD EXCEPTION: " << e.what() << "\n";
      sakardin::freeMatrix(matrix_dyn, rows);
      return STD_EXCEPTION;
    }
  }

  long long max_sum = LLONG_MIN;
  long long now_sum = 0;
  int best_k = 0;
  int j = 0;
  for (int k = -(cols - 1); k <= rows - 1; k++) {
    now_sum = 0;

    for (int i = 0; i < rows; i++) {
      j = i - k;
      if (j < 0 || j >= cols) {
        continue;
      }

      if (mode == "1") {
        now_sum += matrix_stc[i * cols + j];
      } else {
        now_sum += matrix_dyn[i][j];
      }
    }

    if (now_sum > max_sum) {
      max_sum = now_sum;
      best_k = k;
    }
  }

  std::cout << "Max sum: " << max_sum << "\n Diagonal: " << (best_k + cols - 1) << "\n";

  if (mode == "2") {
    sakardin::freeMatrix(matrix_dyn, rows);
  }

  return 0;
}
