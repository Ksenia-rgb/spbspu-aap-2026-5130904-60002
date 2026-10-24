#include <limits>

namespace utils {
  int min(int a, int b)
  {
    if (a < b) {
      return a;
    }
    return b;
  }

  int max(int a, int b)
  {
    if (a > b) {
      return a;
    }
    return b;
  }

  int **allocateMatrix(int r, int c)
  {
    int **const matrix = new int *[r]();
    for (int i = 0; i < r; i++) {
      matrix[i] = new int[c];
    }
    return matrix;
  }

  void freeMatrix(int *const *const matrix, int r)
  {
    if (matrix == nullptr) {
      return;
    }
    for (int i = 0; i < r; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  int minDiagSum(int const *const matrix, int r, int c)
  {
    int min_sum = std::numeric_limits< int >::max();
    int const max_par = max(c, r);
    bool is_plused = false;
    int sum = 0;

    for (int d = 0; d < r; d++) {
      sum = 0;
      is_plused = false;
      for (int step = 0; step < max_par; step++) {
        if (d + step == r || step == c) {
          break;
        }
        sum += matrix[(d + step) * c + step];
        is_plused = true;
      }
      if (is_plused) {
        min_sum = min(min_sum, sum);
      }
    }
    for (int d = 1; d < c; d++) {
      sum = 0;
      is_plused = false;
      for (int step = 0; step < max_par; step++) {
        if (d + step == c || step == r) {
          break;
        }
        sum += matrix[step * c + d + step];
        is_plused = true;
      }
      if (is_plused) {
        min_sum = min(min_sum, sum);
      }
    }

    return min_sum;
  }

  int minDiagSum(int *const *const matrix, int r, int c)
  {
    int min_sum = std::numeric_limits< int >::max();
    int const max_par = max(c, r);
    bool is_plused = false;
    int sum = 0;

    for (int d = 0; d < r; d++) {
      sum = 0;
      is_plused = false;
      for (int step = 0; step < max_par; step++) {
        if (d + step == r || step == c) {
          break;
        }
        sum += matrix[d + step][step];
        is_plused = true;
      }
      if (is_plused) {
        min_sum = min(min_sum, sum);
      }
    }
    for (int d = 1; d < c; d++) {
      sum = 0;
      is_plused = false;
      for (int step = 0; step < max_par; step++) {
        if (d + step == c || step == r) {
          break;
        }
        sum += matrix[step][d + step];
        is_plused = true;
      }
      if (is_plused) {
        min_sum = min(min_sum, sum);
      }
    }

    return min_sum;
  }
}
