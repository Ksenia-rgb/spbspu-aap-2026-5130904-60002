#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

const int MAX_SIZE = 100;

void spiralDecrease(int matrix[][MAX_SIZE], int rows, int cols)
{
  int change = 1;
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;

  while (top <= bottom && left <= right) {
    for (int j = left; j <= right; ++j) {
      matrix[top][j] -= change;
      change++;
    }
    top++;
    for (int i = top; i <= bottom; ++i) {
      matrix[i][right] -= change;
      change++;
    }
    right--;
    if (top <= bottom) {
      for (int j = right; j >= left; --j) {
        matrix[bottom][j] -= change;
        change++;
      }
      bottom--;
    }
    if (left <= right) {
      for (int i = bottom; i >= top; --i) {
        matrix[i][left] -= change;
        change++;
      }
      left++;
    }
  }
}

void spiralDecrease(int** matrix, int rows, int cols)
{
  int change = 1;
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;

  while (top <= bottom && left <= right) {
    for (int j = left; j <= right; ++j) {
      matrix[top][j] -= change;
      change++;
    }
    top++;
    for (int i = top; i <= bottom; ++i) {
      matrix[i][right] -= change;
      change++;
    }
    right--;
    if (top <= bottom) {
      for (int j = right; j >= left; --j) {
        matrix[bottom][j] -= change;
        change++;
      }
      bottom--;
    }
    if (left <= right) {
      for (int i = bottom; i >= top; --i) {
        matrix[i][left] -= change;
        change++;
      }
      left++;
    }
  }
}

int** allocateMatrix(int rows, int cols)
{
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix size <= 0");
  }
  int** const matrix = new int*[rows];
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

void freeMatrix(int** matrix, int rows)
{
  if (matrix != nullptr) {
    for (int i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main(int argc, char* argv[])
{
  const int error_code_content = 2;
  const int error_code_args = 1;

  if (argc != 4) {
    std::cerr << "ERROR: invalid number of arguments\n";
    return error_code_args;
  }

  int memory_var = 0;
  try {
    size_t pos = 0;
    memory_var = std::stoi(argv[1], &pos);
    if (pos != std::string(argv[1]).length()) {
      std::cerr << "ERROR: first parameter is not a valid number\n";
      return error_code_args;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: first parameter is not a number\n";
    return error_code_args;
  } catch (const std::out_of_range& e) {
    std::cerr << "ERROR: first parameter is out of range\n";
    return error_code_args;
  }

  if (memory_var != 1 && memory_var != 2) {
    std::cerr << "ERROR: first parameter is out of range (must be 1 or 2)\n";
    return error_code_args;
  }

  std::ifstream input_file(argv[2]);
  if (!input_file) {
    std::cerr << "ERROR: cannot open file " << argv[2] << '\n';
    return error_code_args;
  }

  std::ofstream out_file(argv[3]);
  if (!out_file) {
    std::cerr << "ERROR: cannot open file " << argv[3] << '\n';
    return error_code_args;
  }

  int rows = 0;
  int cols = 0;
  if (!(input_file >> rows)) {
    std::cerr << "ERROR: cannot read rows from file\n";
    return error_code_content;
  }
  if (!(input_file >> cols)) {
    std::cerr << "ERROR: cannot read cols from file\n";
    return error_code_content;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << "ERROR: invalid matrix dimensions (negative)\n";
    return error_code_content;
  }

  if (rows == 0 || cols == 0) {
    out_file << "0 0\n";
    return 0;
  }

  switch (memory_var) {
  case 1: {
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
      std::cerr << "ERROR: matrix dimensions exceed maximum allowed size for stack allocation\n";
      return error_code_content;
    }
    int matrix1[MAX_SIZE][MAX_SIZE] = {};
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input_file >> matrix1[i][j])) {
          std::cerr << "ERROR: invalid or incomplete matrix data in file\n";
          return error_code_content;
        }
      }
    }
    spiralDecrease(matrix1, rows, cols);
    out_file << rows << " " << cols << " ";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        out_file << matrix1[i][j] << " ";
      }
    }
    break;
  }
  case 2: {
    int** matrix2 = nullptr;
    try {
      matrix2 = allocateMatrix(rows, cols);
    } catch (const std::bad_alloc& e) {
      std::cerr << "ERROR: memory allocation failed\n";
      return error_code_content;
    }
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input_file >> matrix2[i][j])) {
          std::cerr << "ERROR: invalid or incomplete matrix data in file\n";
          freeMatrix(matrix2, rows);
          return error_code_content;
        }
      }
    }
    spiralDecrease(matrix2, rows, cols);
    out_file << rows << " " << cols << " ";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        out_file << matrix2[i][j] << " ";
      }
    }
    freeMatrix(matrix2, rows);
    break;
  }
  default:
    std::cerr << "ERROR: invalid argument\n";
    return error_code_args;
  }

  input_file.close();
  out_file.close();
  return 0;
}
