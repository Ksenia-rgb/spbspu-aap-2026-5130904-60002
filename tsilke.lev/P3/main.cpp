#include <fstream>
#include <iostream>
#include <stdexcept>

const int MAX_SIZE = 100;

void freeMatrix(int **matrix, int n)
{
  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void allocateMatrix(int **(&matrix), int n)
{
  try {
    matrix = new int* [n]{};
    for (int i = 0; i < n; i++) {
      matrix[i] = new int[n]{};
    }
  } catch (...) {
    throw;
  }
}

void printMatrix(int **matrix, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int min(int a, int b)
{
  int n = 0;
  if (a < b) {
    n = a;
  } else {
    n = b;
  }
  return n;
}

void fillMatrix(int (&matrix)[MAX_SIZE][MAX_SIZE], std::ifstream &file, int rows, int cols)
{
  int value = 0;
  const int n = min(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      file >> value;
      if (std::cin.fail()) {
        throw std::invalid_argument("invalid value in file");
      }
      if ((i <= n) && (j <= n)) {
        matrix[i][j] = value;
      }
      if (file.eof() && ((i * j) <= ((rows - 1) * (cols - 1)))) {
        throw std::length_error("Not enough values in matrix");
      }
    }
  }
}

void fillMatrix(int **(&matrix), std::ifstream &file, int rows, int cols)
{
  int value = 0;
  const int n = min(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      file >> value;
      if (std::cin.fail()) {
        throw std::invalid_argument("invalid value in file");
      }
      if ((i <= n) && (j <= n)) {
        matrix[i][j] = value;
      }
      if (file.eof() && ((i * j) <= ((rows - 1) * (cols - 1)))) {
        throw std::length_error("Not enough values in matrix");
      }
    }
  }
}

int cntNzrDig(int (&matrix)[MAX_SIZE][MAX_SIZE], int n)
{
  int count = 0;
  bool zero = false;
  for (int c = 1; c < n; c++) {
    zero = false;
    for (int i = 0; i < n - c; i++) {
      if (matrix[i][c + i] == 0) {
        zero = true;
      }
    }
    if (zero == false) {
      count++;
    }
  }
  for (int c = 1; c < n; c++) {
    zero = false;
    for (int i = 0; i < n - c; i++) {
      if (matrix[c + i][i] == 0) {
        zero = true;
      }
    }
    if (zero == false) {
      count++;
    }
  }
  return count;
}

int cntNzrDig(int **(&matrix), int n)
{
  int count = 0;
  bool zero = false;
  for (int c = 1; c < n; c++) {
    zero = false;
    for (int i = 0; i < n - c; i++) {
      if (matrix[i][c + i] == 0) {
        zero = true;
      }
    }
    if (zero == false) {
      count++;
    }
  }
  for (int c = 1; c < n; c++) {
    zero = false;
    for (int i = 0; i < n - c; i++) {
      if (matrix[c + i][i] == 0) {
        zero = true;
      }
    }
    if (zero == false) {
      count++;
    }
  }
  return count;
}

int main(int argc, char *avgv[])
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  const char* const option = avgv[1];
  try {
    if ((std::stoi(option) != 1) && (std::stoi(option) != 2)) {
      std::cerr << "First parameter out of range\n";
      return 1;
    }
  } catch (...) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  std::ifstream ifile(avgv[2]);
  if (!ifile.is_open()) {
    std::cerr << "ERROR: cannot open input file\n";
    return 2;
  }
  std::ofstream ofile(avgv[3]);
  int result = 0;
  int rows = 0;
  int cols = 0;
  if (!(ifile >> rows >> cols)) {
    std::cerr << "ERROR: empty file\n";
    return 2;
  }
  if (rows < 0 || cols < 0) {
    std::cerr << "ERROR: invalid number of cols or/and rows\n";
    return 2;
  }
  if (rows == 0 || cols == 0) {
    ofile << 0;
    std::cout << "Expects output\n";
    return 0;
  }
  int matrix[MAX_SIZE][MAX_SIZE]{};
  int **matrix_d = nullptr;
  switch (std::stoi(option)) {
  case 1:
    try {
      fillMatrix(matrix, ifile, rows, cols);
      std::cout << "Input matrix: \n";
      printMatrix(matrix, min(rows, cols));
      result = cntNzrDig(matrix, min(rows, cols));
    } catch (std::invalid_argument &e) {
      std::cerr << "ERROR: " << e.what() << "\n";
      return 2;
    } catch (std::length_error &e) {
      std::cerr << "ERROR: " << e.what() << "\n";
      return 2;
    }
    break;
  case 2:
    try {
      allocateMatrix(matrix_d, min(rows, cols));
      fillMatrix(matrix_d, ifile, rows, cols);
      std::cout << "Input matrix: \n";
      printMatrix(matrix_d, min(rows, cols));
      result = cntNzrDig(matrix_d, min(rows, cols));
      freeMatrix(matrix_d, min(rows, cols));
    } catch (std::invalid_argument &e) {
      std::cerr << "ERROR: " << e.what() << "\n";
      freeMatrix(matrix_d, min(rows, cols));
      return 2;
    } catch (std::length_error &e) {
      freeMatrix(matrix_d, min(rows, cols));
      std::cerr << "ERROR: " << e.what() << "\n";
      return 2;
    } catch (...) {
      freeMatrix(matrix_d, min(rows, cols));
      std::cerr << "ERROR: bad alloc\n";
      return 2;
    }
    break;
  }
  ofile << result;
  std::cout << "Expects output\n";
  return 0;
}
