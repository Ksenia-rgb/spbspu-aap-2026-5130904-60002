#include <iostream>
#include <fstream>
#include <string>

const int max_size = 10000;

int localMin(const int* matrix, int rows, int cols)
{
  int count = 0;

  if (rows < 3 || cols < 3) {
    return 0;
  }

  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j) {
      const int center = matrix[i * cols + j];

      if (matrix[(i - 1) * cols + (j - 1)] > center && matrix[(i - 1) * cols + j] > center
          && matrix[(i - 1) * cols + (j + 1)] > center && matrix[i * cols + (j - 1)] > center
          && matrix[i * cols + (j + 1)] > center && matrix[(i + 1) * cols + (j - 1)] > center
          && matrix[(i + 1) * cols + j] > center && matrix[(i + 1) * cols + (j + 1)] > center) {
        count++;
      }
    }
  }

  return count;
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Error\n";
    return 1;
  }

  const std::string num = argv[1];
  const std::string input_file = argv[2];
  const std::string output_file = argv[3];

  int var = 0;

  if (num == "1") {
    var = 1;
  } else if (num == "2") {
    var = 2;
  } else {
    std::cerr << "Error\n";
    return 1;
  }

  int rows = 0;
  int cols = 0;

  int* dynamic_matrix = nullptr;
  int static_matrix[max_size] = {};
  int* matrix = nullptr;

  std::ifstream file(input_file);

  if (!file.is_open()) {
    std::cerr << "Error\n";
    return 2;
  }

  if (!(file >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error\n";
    return 2;
  }

  if ((rows == 0) != (cols == 0)) {
    std::cerr << "Error\n";
    return 2;
  }

  if (rows != 0 && cols > max_size / rows) {
    std::cerr << "Error\n";
    return 2;
  }

  const int total = rows * cols;

  if (var == 1) {
    matrix = static_matrix;
  } else if (var == 2) {
    dynamic_matrix = new int[rows * cols];
    matrix = dynamic_matrix;
  }

  for (int i = 0; i < total; ++i) {
    if (!(file >> matrix[i])) {
      std::cerr << "Error\n";

      if (var == 2) {
        delete[] dynamic_matrix;
      }

      return 2;
    }
  }

  file.close();

  const int result = localMin(matrix, rows, cols);

  std::ofstream out_file(output_file);

  if (!out_file.is_open()) {
    std::cerr << "Error\n";

    if (var == 2) {
      delete[] dynamic_matrix;
    }

    return 2;
  }

  out_file << result << '\n';

  if (!out_file) {
    std::cerr << "Error\n";

    if (var == 2) {
      delete[] dynamic_matrix;
    }

    return 2;
  }

  out_file.close();

  if (var == 2) {
    delete[] dynamic_matrix;
  }

  return 0;
}
