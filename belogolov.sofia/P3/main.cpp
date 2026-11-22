#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

const int max_size = 100;

void lftBotClk(int matrix[][max_size], int rows, int cols)
{
  int change = 1;

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;

  while (top <= bottom && left <= right) {
    for (int i = bottom; i >= top; --i) {
      matrix[i][left] -= change;
      change++;
    }
    left++;
    if (left > right) {
      break;
    }
    for (int j = left; j <= right; j++) {
      matrix[top][j] -= change;
      change++;
    }
    top++;
    if (top > bottom) {
      break;
    }
    for (int i = top; i <= bottom; ++i) {
      matrix[i][right] -= change;
      change++;
      if (top > bottom) {
        break;
      }
    }
    right--;
    if (right < left) {
      break;
    }
    for (int j = right; j >= left; --j) {
      matrix[bottom][j] -= change;
      change++;
    }
    bottom--;
  }
}
void lftBotClk(int** matrix, int rows, int cols)
{
  int change = 1;

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;

  while (top <= bottom && left <= right) {
    for (int i = bottom; i >= top; --i) {
      matrix[i][left] -= change;
      change++;
    }
    left++;
    if (left > right) {
      break;
    }
    for (int j = left; j <= right; j++) {
      matrix[top][j] -= change;
      change++;
    }
    top++;
    if (top > bottom) {
      break;
    }
    for (int i = top; i <= bottom; ++i) {
      matrix[i][right] -= change;
      change++;
      if (top > bottom) {
        break;
      }
    }
    right--;
    if (right < left) {
      break;
    }
    for (int j = right; j >= left; --j) {
      matrix[bottom][j] -= change;
      change++;
    }
    bottom--;
  }
}

int** allocateMatrix(int rows, int cols)
{
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix size <=0");
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
  for (int i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}
int main(int argc, char* argv[])
{
  const int error_code = 2;
  if (argc != 4) {
    std::cerr << "ERROR: invalid number of arguments" << '\n';
    return 1;
  }

  std::ifstream input_file(argv[2]);
  if (!input_file) {
    std::cerr << "ERROR: cannot open file " << argv[2] << '\n';
    return 1;
  }
  std::ofstream out_file(argv[3]);
  if (!out_file) {
    std::cerr << "ERROR: cannot open file " << argv[3] << '\n';
    return 1;
  }

  int memory_var = 0;
  try {
    memory_var = std::stoi(argv[1]);
  } catch (const std::invalid_argument& e) {
    std::cerr << "ERROR: invalid argument for memory\n";
    return 1;
  } catch (std::out_of_range& e) {
    std::cerr << "ERROR: out of range\n";
    return 1;
  }

  int rows = 0;
  int cols = 0;
  if (!(input_file >> rows)) {
    std::cerr << "ERROR: invalid argument\n";
    return error_code;
  }
  if (!(input_file >> cols)) {
    std::cerr << "ERROR: invalid argument\n";
    return error_code;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << "ERROR: invalid argument\n";
    return error_code;
  }
  if (rows == 0 || cols == 0) {
    out_file << "0 0";
    return 0;
  }
  switch (memory_var) {
  case 1: {
    int matrix1[max_size][max_size] = {};

    if (rows > max_size || cols > max_size) {
      std::cerr << "ERROR: invalid argument\n";
      return error_code;
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input_file >> matrix1[i][j])) {
          std::cerr << "ERROR: invalid argument\n";
          return error_code;
        }
      }
    }
    lftBotClk(matrix1, rows, cols);

    out_file << rows << " " << cols << " ";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        out_file << matrix1[i][j] << " ";
      }
    }
    break;
  }
  case 2: {
    int** const matrix2 = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input_file >> matrix2[i][j])) {
          std::cerr << "ERROR: invalid argument\n";
          freeMatrix(matrix2, rows);
          return error_code;
        }
      }
    }
    lftBotClk(matrix2, rows, cols);
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
    return 1;
  }
  input_file.close();
  out_file.close();
  return 0;
}
