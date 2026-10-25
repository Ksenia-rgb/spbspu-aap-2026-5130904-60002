#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace oz {
  const int argument_error_code = 1;
  const int file_error_code = 2;
  const int fixed_capacity = 10000;

  bool parseMode(const char* text, int& mode)
  {
    if (std::strcmp(text, "1") == 0) {
      mode = 1;
      return true;
    }
    if (std::strcmp(text, "2") == 0) {
      mode = 2;
      return true;
    }
    return false;
  }

  bool readDimensions(std::ifstream& input, int& rows, int& columns, int& count)
  {
    long long readRows = 0;
    long long readColumns = 0;

    if (!(input >> readRows >> readColumns)) {
      return false;
    }

    if (readRows == 0 && readColumns == 0) {
      rows = 0;
      columns = 0;
      count = 0;
      return true;
    }

    if (readRows <= 0 || readColumns <= 0 || readRows > std::numeric_limits< int >::max()
        || readColumns > std::numeric_limits< int >::max()) {
      return false;
    }

    const long long product = readRows * readColumns;
    if (product > std::numeric_limits< int >::max()) {
      return false;
    }

    rows = static_cast< int >(readRows);
    columns = static_cast< int >(readColumns);
    count = static_cast< int >(product);
    return true;
  }

  bool hasNoExtraData(std::ifstream& input)
  {
    input >> std::ws;
    return input.eof();
  }

  bool readElements(std::ifstream& input, int* values, int count)
  {
    for (int i = 0; i < count; ++i) {
      if (!(input >> values[i])) {
        return false;
      }
    }

    return hasNoExtraData(input);
  }

  bool calculateMaxSum(const int* values, int rows, int columns, long long& result)
  {
    if (rows == 0 && columns == 0) {
      result = 0;
      return true;
    }

    bool found = false;
    long long maxSum = std::numeric_limits< long long >::lowest();

    const int lastDiagonal = rows + columns - 2;
    const int secondaryDiagonal = columns - 1;

    for (int diagonal = 0; diagonal <= lastDiagonal; ++diagonal) {
      if (diagonal == secondaryDiagonal) {
        continue;
      }

      long long sum = 0;
      bool hasElement = false;

      for (int row = 0; row < rows; ++row) {
        const int column = diagonal - row;

        if (column >= 0 && column < columns) {
          sum += values[row * columns + column];
          hasElement = true;
        }
      }

      if (hasElement && (!found || sum > maxSum)) {
        maxSum = sum;
        found = true;
      }
    }

    result = found ? maxSum : 0;
    return true;
  }

  bool writeResult(const char* path, long long result)
  {
    std::ofstream output(path);
    if (!output) {
      std::cerr << "Cannot open output file\n";
      return false;
    }

    output << result << '\n';
    if (!output) {
      std::cerr << "Cannot write output file\n";
      return false;
    }

    return true;
  }

  int processFixed(std::ifstream& input, const char* outputPath, int rows, int columns, int count)
  {
    if (count > fixed_capacity) {
      std::cerr << "Matrix is too large for fixed storage\n";
      return file_error_code;
    }

    int values[fixed_capacity];

    if (count == 0) {
      if (!hasNoExtraData(input)) {
        std::cerr << "Invalid input file\n";
        return file_error_code;
      }
    } else if (!readElements(input, values, count)) {
      std::cerr << "Invalid input file\n";
      return file_error_code;
    }

    long long result = 0;
    calculateMaxSum(values, rows, columns, result);

    return writeResult(outputPath, result) ? 0 : file_error_code;
  }

  int processDynamic(std::ifstream& input, const char* outputPath, int rows, int columns, int count)
  {
    if (count == 0) {
      if (!hasNoExtraData(input)) {
        std::cerr << "Invalid input file\n";
        return file_error_code;
      }
      return writeResult(outputPath, 0) ? 0 : file_error_code;
    }

    int* values = new (std::nothrow) int[count];
    if (values == nullptr) {
      std::cerr << "Cannot allocate matrix\n";
      return file_error_code;
    }

    if (!readElements(input, values, count)) {
      delete[] values;
      std::cerr << "Invalid input file\n";
      return file_error_code;
    }

    long long result = 0;
    calculateMaxSum(values, rows, columns, result);
    delete[] values;

    return writeResult(outputPath, result) ? 0 : file_error_code;
  }

  int run(int argc, char* argv[])
  {
    if (argc != 4) {
      std::cerr << "Expected: lab num input output\n";
      return argument_error_code;
    }

    int mode = 0;
    if (!parseMode(argv[1], mode)) {
      std::cerr << "First parameter must be 1 or 2\n";
      return argument_error_code;
    }

    std::ifstream input(argv[2]);
    if (!input) {
      std::cerr << "Cannot open input file\n";
      return file_error_code;
    }

    int rows = 0;
    int columns = 0;
    int count = 0;

    if (!readDimensions(input, rows, columns, count)) {
      std::cerr << "Invalid input file\n";
      return file_error_code;
    }

    if (mode == 1) {
      return processFixed(input, argv[3], rows, columns, count);
    }

    return processDynamic(input, argv[3], rows, columns, count);
  }
}

int main(int argc, char* argv[])
{
  return oz::run(argc, argv);
}
