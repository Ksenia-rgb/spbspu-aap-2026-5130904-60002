#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
const size_t max_size = 10000;

void check_arguments(const int argc, char* argv[])
{
  if (argc < 4) {
    throw std::invalid_argument("Not enough arguments");
  }
  if (argc > 4) {
    throw std::invalid_argument("Too many arguments");
  }
  size_t pos;
  if (argv[1][pos] != '\0') {
    throw std::invalid_argument("First parameter is not a number");
  }
  if (std::stoi(argv[1]) != 1 && std::stoi(argv[1]) != 2) {
    throw std::out_of_range("First parametr out of range");
  }
}

int** allocateMatrix(int** m, int rows, int cols)
{
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Invalid rows or colums");
  }

  int** matrix = new int* [rows]
  {
  };

  try {
    for (size_t i = 0; i < rows; i++) {
      matrix[i] = new int[cols]{};
    }
  } catch (...) {
    for (size_t i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }
  return matrix;
}
void freeMatrix(int** m, int rows, int cols)
{
  for (size_t i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

void check_matrix_in_file(std::ifstream& ifile)
{
  int rows;
  int cols;
  if (!(ifile >> rows >> cols)) {
    throw std::runtime_error("Error! Code 2");
  }
  int x;
  size_t count_in_file = 0;
  while (ifile >> x) {
    count_in_file++;
  }
  if (count_in_file != (rows * cols)) {
    throw std::runtime_error("Error: incorrect matrix");
  }
}

void fillMatrix(int arr[max_size], size_t rows, size_t cols, std::ifstream& ifile)
{
  size_t i = 0;
  int x;
  while (ifile >> x) {
    arr[i] = x;
    i++;
  }
}
void fillMatrix(int** matrix, size_t rows, size_t cols, std::ifstream& ifile)
{
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ifile >> matrix[i][j];
    }
  }
}
int num_rows_max_len_equal(const int arr[], size_t rows, size_t cols)
{
  int num_rows_with_max = 1;
  size_t max_len = 1;
  for (size_t i = 0; i < rows; i++) {
    size_t curr_len = 1;
    for (size_t j = 1; j < cols; j++) {
      if (arr[i * cols + j] == arr[i * cols + j - 1]) {
        curr_len++;
        if (curr_len > max_len) {
          max_len = curr_len;
          num_rows_with_max = i + 1;
        }
      } else {
        curr_len = 1;
      }
    }
  }
  return num_rows_with_max;
}
int num_rows_max_len_equal(int** matrix, size_t rows, size_t cols)
{
  int num_rows_with_max = 0;
  size_t max_len = 1;
  for (size_t i = 0; i < rows; i++) {
    size_t curr_len = 1;
    for (size_t j = 1; j < cols; j++) {
      if (matrix[i][j] == matrix[i][j - 1]) {
        curr_len++;
        if (curr_len > max_len) {
          max_len = curr_len;
          num_rows_with_max = i + 1;
        }
      } else {
        curr_len = 1;
      }
    }
  }
  return num_rows_with_max;
}
int main(int argc, char* argv[])
{
  const int mode = std::stoi(argv[1]);

  std::ifstream ifile(argv[2]);
  try {
    check_arguments(argc, argv);
    check_matrix_in_file(ifile);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what();
    return 2;
  }
  ifile.clear();
  ifile.seekg(0);
  int rows;
  int cols;
  ifile >> rows >> cols;

  int num_rows_max_equal;
  if (mode == 1) {
    int arr[max_size]{};
    fillMatrix(arr, rows, cols, ifile);
    num_rows_max_equal = num_rows_max_len_equal(arr, rows, cols);
  } else {
    int** matrix{};
    try {
      matrix = allocateMatrix(matrix, rows, cols);
    } catch (const std::exception& e) {
      std::cerr << e.what();
      freeMatrix(matrix, rows, cols);
      return 3;
    }
    fillMatrix(matrix, rows, cols, ifile);
    num_rows_max_equal = num_rows_max_len_equal(matrix, rows, cols);
    freeMatrix(matrix, rows, cols);
    matrix = nullptr;
  }
  ifile.close();

  std::ofstream ofile(argv[3]);

  ofile << num_rows_max_equal;

  ofile.close();
  return 0;
}
