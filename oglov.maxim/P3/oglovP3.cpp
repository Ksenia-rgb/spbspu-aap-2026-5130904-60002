#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <cstddef>

const size_t max_size = 10000;

void checkArguments(const int argc, char* argv[])
{
  if (argc < 4) {
    throw std::invalid_argument("Not enough arguments");
  }
  if (argc > 4) {
    throw std::invalid_argument("Too many arguments");
  }
  size_t pos = 0;
  std::stoi(argv[1], &pos);
  if (argv[1][pos] != '\0') {
    throw std::invalid_argument("First parameter is not a number");
  }
  const int mode = std::stoi(argv[1]);
  if (mode != 1 && mode != 2) {
    throw std::out_of_range("First parametr out of range");
  }
}

int** allocateMatrix(const int rows, const int cols)
{
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Invalid rows or colums");
  }

  int** const matrix = new int* [static_cast< size_t >(rows)]
  {
  };

  try {
    for (size_t i = 0; i < static_cast< size_t >(rows); i++) {
      matrix[i] = new int[static_cast< size_t >(cols)]{};
    }
  } catch (...) {
    for (size_t i = 0; i < static_cast< size_t >(rows); i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }
  return matrix;
}

void freeMatrix(int** m, const int rows)
{
  if (m == nullptr) {
    return;
  }
  for (size_t i = 0; i < static_cast< size_t >(rows); i++) {
    delete[] m[i];
  }
  delete[] m;
}

void checkMatrixInFile(std::ifstream& ifile)
{
  int rows = 0;
  int cols = 0;
  if (!(ifile >> rows >> cols)) {
    throw std::runtime_error("Error! Code 2");
  }
  if (rows < 1 || cols < 1) {
    throw std::runtime_error("Error: incorrect matrix size");
  }
  size_t count_in_file = 0;
  int x = 0;
  while (ifile >> x) {
    count_in_file++;
  }
  if (count_in_file != static_cast< size_t >(rows) * static_cast< size_t >(cols)) {
    throw std::runtime_error("Error: incorrect matrix");
  }
}

void fillMatrix(int arr[max_size], std::ifstream& ifile)
{
  size_t i = 0;
  int x = 0;
  while (ifile >> x && i < max_size) {
    arr[i] = x;
    i++;
  }
}

void fillMatrix(int** matrix, const size_t rows, const size_t cols, std::ifstream& ifile)
{
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ifile >> matrix[i][j];
    }
  }
}

int numRowsMaxLenEqual(const int arr[], const size_t rows, const size_t cols)
{
  int num_rows_with_max = 0;
  size_t max_len = 0;
  for (size_t i = 0; i < rows; i++) {
    size_t curr_len = 1;
    for (size_t j = 1; j < cols; j++) {
      if (arr[i * cols + j] == arr[i * cols + j - 1]) {
        curr_len++;
      } else {
        curr_len = 1;
      }
      if (curr_len > max_len) {
        max_len = curr_len;
        num_rows_with_max = static_cast< int >(i) + 1;
      }
    }
    if (cols == 1 && max_len == 0) {
      max_len = 1;
      num_rows_with_max = static_cast< int >(i) + 1;
    }
  }
  return num_rows_with_max;
}

int numRowsMaxLenEqual(int** matrix, const size_t rows, const size_t cols)
{
  int num_rows_with_max = 0;
  size_t max_len = 0;
  for (size_t i = 0; i < rows; i++) {
    size_t curr_len = 1;
    for (size_t j = 1; j < cols; j++) {
      if (matrix[i][j] == matrix[i][j - 1]) {
        curr_len++;
      } else {
        curr_len = 1;
      }
      if (curr_len > max_len) {
        max_len = curr_len;
        num_rows_with_max = static_cast< int >(i) + 1;
      }
    }
    if (cols == 1 && max_len == 0) {
      max_len = 1;
      num_rows_with_max = static_cast< int >(i) + 1;
    }
  }
  return num_rows_with_max;
}

int main(int argc, char* argv[])
{
  try {
    checkArguments(argc, argv);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << e.what();
    return 1;
  }

  const int mode = std::stoi(argv[1]);

  std::ifstream ifile(argv[2]);
  try {
    checkMatrixInFile(ifile);
  } catch (const std::runtime_error& e) {
    std::cerr << e.what();
    return 2;
  }

  ifile.clear();
  ifile.seekg(0);
  int rows = 0;
  int cols = 0;
  ifile >> rows >> cols;

  int num_rows_max_equal = 0;
  if (mode == 1) {
    int arr[max_size]{};
    fillMatrix(arr, ifile);
    num_rows_max_equal = numRowsMaxLenEqual(arr, static_cast< size_t >(rows), static_cast< size_t >(cols));
  } else {
    int** matrix = nullptr;
    try {
      matrix = allocateMatrix(rows, cols);
    } catch (const std::exception& e) {
      std::cerr << e.what();
      return 3;
    }
    fillMatrix(matrix, static_cast< size_t >(rows), static_cast< size_t >(cols), ifile);
    num_rows_max_equal = numRowsMaxLenEqual(matrix, static_cast< size_t >(rows), static_cast< size_t >(cols));
    freeMatrix(matrix, rows);
  }
  ifile.close();

  std::ofstream ofile(argv[3]);
  ofile << num_rows_max_equal;
  ofile.close();
  return 0;
}
