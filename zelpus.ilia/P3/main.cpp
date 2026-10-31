#include <iostream>
#include <string>
#include <fstream>

const int MAX_SIZE = 100;

bool readSizes(std::ifstream& in, int& rows, int& cols)
{
  if (!(in >> rows >> cols)) {
    return false;
  }
  if (rows < 0 || cols < 0) {
    return false;
  }
  return true;
}

int** allocateMatrix(int rows, int cols)
{
  int** const m = new int*[rows]();
  try {
    for (int i = 0; i < rows; ++i) {
      m[i] = new int[cols]();
    }
  } catch (...) {
    for (int i = 0; i < rows; i++) {
      delete[] m[i];
    }
    delete[] m;
    throw;
  }
  return m;
}

int findLocalMinDyn(const int* const* const m, int rows, int cols)
{
  int count = 0;
  for (int i = 1; i < (rows - 1); i++) {
    for (int j = 1; j < (cols - 1); j++) {
      if ((m[i][j] < m[i - 1][j]) && (m[i][j] < m[i + 1][j]) && (m[i][j] < m[i][j - 1]) && (m[i][j] < m[i][j + 1])) {
        count += 1;
      }
    }
  }
  return count;
}

int findLocalMinStack(int m[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
  int count = 0;
  for (int i = 1; i < (rows - 1); i++) {
    for (int j = 1; j < (cols - 1); j++) {
      if ((m[i][j] < m[i - 1][j]) && (m[i][j] < m[i + 1][j]) && (m[i][j] < m[i][j - 1]) && (m[i][j] < m[i][j + 1])) {
        count += 1;
      }
    }
  }
  return count;
}

void freeMatrix(int* const* const m, int rows)
{
  if (m == nullptr) {
    return;
  }
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

bool readToDyn(std::ifstream& in, int* const* const matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!(in >> matrix[i][j])) {
        return false;
      }
    }
  }
  return true;
}

bool readToStack(std::ifstream& in, int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!(in >> matrix[i][j])) {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << "mode input_file output_file\n";
    return 1;
  }

  const std::string inputFile = argv[2];
  const std::string outputFile = argv[3];
  const std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "ERROR: mode must be number from 1 to 2!\n";
    return 1;
  }

  std::ifstream in(inputFile);
  if (!in) {
    std::cerr << "Error: cannot open " << inputFile << "\n";
    return 2;
  }

  int rows = 0, cols = 0;
  if (!readSizes(in, rows, cols)) {
    std::cerr << "ERROR: invalid sizes\n";
    return 2;
  }

  if (rows > MAX_SIZE || cols > MAX_SIZE) {
    std::cerr << "ERROR: matrix too large (max " << "x" << MAX_SIZE << ")\n";
    return 2;
  }

  int result = 0;
  if (mode == "1") {
    int matrix[MAX_SIZE][MAX_SIZE];
    if (!readToStack(in, matrix, rows, cols)) {
      std::cerr << "ERROR: bad matrix element\n";
      return 2;
    }
    result = findLocalMinStack(matrix, rows, cols);
  } else {
    int* const* matrix = nullptr;
    try {
      matrix = allocateMatrix(rows, cols);
    } catch (...) {
      std::cerr << "ERROR: cannot allocate matrix\n";
      return 2;
    }
    if (!readToDyn(in, matrix, rows, cols)) {
      std::cerr << "ERROR: bad matrix element\n";
      freeMatrix(matrix, rows);
      return 2;
    }
    result = findLocalMinDyn(matrix, rows, cols);
    freeMatrix(matrix, rows);
  }

  std::ofstream out(outputFile);
  if (!out) {
    std::cerr << "ERROR: write failed\n";
    return 2;
  }
  out << result << "\n";
  return 0;
}
