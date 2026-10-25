#include <iostream>
#include <climits>

#include "testlib/sakardin.h"

const int MAX_SIZE = 10000;
const int INVALID_ARGUMENT_ERROR = 2;
const int STD_EXCEPTION = 3;

int main(int argc, char* argv[])
{
  int matrixStc[MAX_SIZE];
  int** matrixDyn = nullptr;

  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <num> <input> <output>\n";
    return 1;
  }
  std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "Unsuitable num. (Possible num: 1, 2)\n";
    return 1;
  }

  std::ifstream fileIn = sakardin::openInputFile(argv[2]);
  if (!fileIn.is_open()) {
    return 1;
  }

  int rows, cols;
  if (!(fileIn >> rows >> cols)) {
    std::cerr << "ERROR: Error reading matrix size\n";
    return 1;
  }

  if (mode == "1") {
    if (rows * cols > MAX_SIZE || rows <= 0 || cols <= 0) {
      std::cerr << "ERROR: incorrect matrix size values\n";
      return 1;
    }

    for (int i = 0; i < rows * cols; i++) {
      if (!(fileIn >> matrixStc[i])) {
        std::cerr << "ERROR: Error reading matrix data\n";
        return 1;
      }
    }

    fileIn.close();
  }

  if (mode == "2") {
    try {
      matrixDyn = sakardin::allocateMatrix(rows, cols);
      sakardin::fillMatrixInputFile(matrixDyn, rows, cols, fileIn);
      fileIn.close();
    }

    catch (const std::invalid_argument& e) {
      std::cerr << "INVALID ARGUMENT ERROR: " << e.what() << "\n";
      sakardin::freeMatrix(matrixDyn, rows);
      return INVALID_ARGUMENT_ERROR;
    }
    catch (const std::exception& e) {
      std::cerr << "STD EXCEPTION: " << e.what() << "\n";
      sakardin::freeMatrix(matrixDyn, rows);
      return STD_EXCEPTION;
    }
  }

  long long maxSum = LLONG_MIN;
  long long nowSum = 0;
  int bestK = 0;
  int j = 0;
  for (int k = -(cols - 1); k <= rows - 1; k++) {
    nowSum = 0;

    for (int i = 0; i < rows; i++) {
      j = i - k;
      if (j < 0 || j >= cols) continue;

      if (mode == "1") {
        nowSum += matrixStc[i * cols + j];
      }
      else {
        nowSum += matrixDyn[i][j];
      }
    }

    if (nowSum > maxSum) {
      maxSum = nowSum;
      bestK = k;
    }
  }

  std::cout << "Max sum: " << maxSum << "\n Diagonal: " << (bestK + cols - 1) << "\n";

  if (mode == "2") {
    sakardin::freeMatrix(matrixDyn, rows);
  }

  return 0;
}
