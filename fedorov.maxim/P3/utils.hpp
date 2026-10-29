#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {
  int min(int a, int b);
  int **allocateMatrix(int r, int c);
  void freeMatrix(int *const *matrix, int r);
  int minDiagSum(int const *matrix, int r, int c);
  int minDiagSum(int *const *matrix, int r, int c);
}

#endif
