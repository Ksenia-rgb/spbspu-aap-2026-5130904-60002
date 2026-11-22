#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
const int MAX_SIZE = 100;

int **allocateMatrix(int rows, int cols)
{
  if ((rows <= 0) || (cols <= 0)) {
    throw std::invalid_argument("matrix size <= 0");
  }
  int **const matrix = new int *[rows];
  try {
    for (int i = 0; i < rows; ++i) {
      matrix[i] = new int[cols]{};
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

void freeMatrix(int **m, int rows)
{
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

int sdlMatrix(int **matrix, int rows, int cols)
{
  int count = 0;
  for (int i = 0; i < rows; ++i) {
    int min_row = matrix[i][0];
    for (int j = 1; j < cols; ++j) {
      if (matrix[i][j] < min_row) {
        min_row = matrix[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == min_row) {
        bool sdl = true;
        for (int k = 0; k < rows; k++) {
          if (matrix[k][j] > min_row) {
            sdl = false;
            break;
          }
        }
        if (sdl) {
          count++;
        }
      }
    }
  }
  return count;
}

int sdlMatrix1(int (*matrix)[MAX_SIZE], int rows, int cols)
{
  int count = 0;
  for (int i = 0; i < rows; ++i) {
    int min_row = matrix[i][0];
    for (int j = 1; j < cols; ++j) {
      if (matrix[i][j] < min_row) {
        min_row = matrix[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == min_row) {
        bool sdl = true;
        for (int k = 0; k < rows; k++) {
          if (matrix[k][j] > min_row) {
            sdl = false;
            break;
          }
        }
        if (sdl) {
          count++;
        }
      }
    }
  }
  return count;
}

int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (argv[1][0] < '0' || argv[1][0] > '9' || argv[1][1] != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  const int num = std::stoi(argv[1]);
  if (num < 1 || num > 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "ERROR: can not open file\n";
    return 2;
  }
  int result = 0;
  int rows = 0;
  int cols = 0;
  if (!(input >> rows)) {
    std::cerr << "ERROR: invalid_argument\n";
    return 2;
  }
  if (!(input >> cols)) {
    std::cerr << "ERROR: invalid_argument\n";
    return 2;
  }
  if (rows == 0 || cols == 0) {
    std::ofstream output(argv[3]);
    output << 0;
    return 0;
  } else if (rows < 0 || cols < 0) {
    std::cerr << "ERROR: wrong size\n";
    return 2;
  }

  if (num == 1) {
    int arr[MAX_SIZE][MAX_SIZE] = {};
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
      std::cerr << "ERROR: too large matrix";
      return 2;
    }
    int x = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input >> x)) {
          std::cerr << "ERROR: invalid_argument\n";
          return 2;
        }
        arr[i][j] = x;
      }
    }
    result = sdlMatrix1(arr, rows, cols);
  }
  if (num == 2) {
    int **const arr = allocateMatrix(rows, cols);
    int x = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input >> x)) {
          std::cerr << "ERROR: invalid_argument\n";
          freeMatrix(arr, rows);
          return 2;
        }
        arr[i][j] = x;
      }
    }
    result = sdlMatrix(arr, rows, cols);
    freeMatrix(arr, rows);
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "ERROR: can not open file\n";
    return 2;
  }
  output << result << "\n";
  return 0;
}
