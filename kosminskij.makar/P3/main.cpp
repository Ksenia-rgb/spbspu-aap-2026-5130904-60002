#include <iostream>
#include <fstream>
#include <new>
#include <string>

const int MAX_SIZE = 10000;

void freeMatrix(int** matrix, int rows)
{
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** allocateMatrix(int rows, int cols)
{
  int** matrix = new int*[rows]{};

  try {
    for (int i = 0; i < rows; i++) {
      matrix[i] = new int[cols]{};
    }
  }
  catch (...) {
    freeMatrix(matrix, rows);
    throw;
  }

  return matrix;
}

bool readMatrix(int** m, int rows, int cols, std::ifstream& in)
{
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!(in >> m[i][j])) {
        return false;
      }
    }
  }
  char c;
  if (in >> c) {
    return false;
  }
  return true;
}


int countColumns(int** m, int rows, int cols)
{
  int count = 0;
  for (int j = 0; j < cols; ++j) {
    bool ok = true;
    for (int i = 0; i + 1 < rows; ++i) {
      if (m[i][j] == m[i + 1][j]) {
        ok = false;
        break;
      }
    }
    if (ok) {
      ++count;
    }
  }
  return count;
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <num> <input> <output>\n";
    return 1;
  }

  std::string num = argv[1];
  std::string inputFile = argv[2];
  std::string outputFile = argv[3];

  if (num != "1" && num != "2") {
    std::cerr << "ERROR: first parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream in(inputFile);
  if (!in) {
    std::cerr << "ERROR: cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "ERROR: input is not a 2D array\n";
    return 2;
  }

  int result = 0;

  if (num == "2") {
    int** matrix = nullptr;
    try {
      matrix = allocateMatrix(rows, cols);
    }
    catch (const std::bad_alloc&) {
      std::cerr << "ERROR: not enough memory\n";
      return 2;
    }

    if (!readMatrix(matrix, rows, cols, in)) {
      freeMatrix(matrix, rows);
      std::cerr << "ERROR: input is not a 2D array\n";
      return 2;
    }

    result = countColumns(matrix, rows, cols);
    freeMatrix(matrix, rows);
  }
  else {
    if (static_cast<long long>(rows) * cols > MAX_SIZE) {
      std::cerr << "ERROR: matrix is too big\n";
      return 2;
    }

    int data[MAX_SIZE];
    int* matrix[MAX_SIZE];
    for (int i = 0; i < rows; ++i) {
      matrix[i] = data + i * cols;
    }

    if (!readMatrix(matrix, rows, cols, in)) {
      std::cerr << "ERROR: input is not a 2D array\n";
      return 2;
    }

    result = countColumns(matrix, rows, cols);
  }

  std::ofstream out(outputFile);
  if (!out) {
    std::cerr << "ERROR: cannot open output file\n";
    return 1;
  }
  out << result << "\n";

  return 0;
}
