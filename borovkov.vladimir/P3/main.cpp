#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <new>

const int max_rows = 100;
const int max_cols = 100;
const int count_argc = 4;
const int variant_stack = 1;
const int variant_heap = 2;
constexpr int invalid_terminal_elements = 1;
constexpr int invalid_elements_in_file = 2;

void deleteMatrix(int** matrix, int rows)
{
  for (int i = 0; i < rows; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** createMatrix(int rows, int cols)
{
  int** const matrix = new int*[rows]();
  try
  {
    for (int i = 0; i < rows; i++)
    {
      matrix[i] = new int[cols]();
    }
    return matrix;
  }
  catch (...)
  {
    deleteMatrix(matrix, rows);
    throw;
  }
}

int main(int argc, char* argv[])
{
  if (argc < count_argc)
  {
    std::cerr << "Not enough arguments";
    return invalid_terminal_elements;
  }
  if (argc > count_argc)
  {
    std::cerr << "Too many arguments";
    return invalid_terminal_elements;
  }
  if (argc == count_argc)
  {
    const char* const name_input = argv[2];
    const char* const name_output = argv[3];
    int variant = 0;
    try
    {
      variant = std::stoi(argv[1]);
      if (variant != variant_stack && variant != variant_heap)
      {
        throw std::out_of_range("First parametr is out of range");
      }
    }
    catch (const std::invalid_argument&)
    {
      std::cerr << "First parameter is not a number";
      return invalid_terminal_elements;
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "First parametr is out of range";
      return invalid_terminal_elements;
    }
    if (variant == variant_stack)
    {
      std::ifstream file_input(name_input);
      if (!file_input.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      if (file_input.peek() == std::ifstream::traits_type::eof())
      {
        std::cerr << "File is empty";
        return invalid_elements_in_file;
      }
      int matrix[max_rows][max_cols];
      int rows = 0;
      int cols = 0;
      if (!(file_input >> rows) || !(file_input >> cols))
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      if (rows < 0 || cols < 0)
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          int x = 0;
          if (!(file_input >> x))
          {
            std::cerr << "Incorrect element in file";
            return invalid_elements_in_file;
          }
          matrix[i][j] = x;
        }
      }
      file_input.close();
      if (rows == 0 || cols == 0)
      {
        std::ofstream file_output(name_output);
        if (!file_output.is_open())
        {
          std::cerr << "File can not open";
          return invalid_elements_in_file;
        }
        file_output << rows << " " << cols;
        file_output.close();
        return 0;
      }
      int rows_start = 0;
      int rows_end = rows - 1;
      int cols_start = 0;
      int cols_end = cols - 1;
      int increment = 1;
      while (rows_start <= rows_end && cols_start <= cols_end)
      {
        for (int i = cols_start; i <= cols_end; i++)
        {
          matrix[rows_end][i] += increment;
          increment++;
        }
        rows_end--;
        if (rows_start <= rows_end)
        {
          for (int i = rows_end; i >= rows_start; i--)
          {
            matrix[i][cols_end] += increment;
            increment++;
          }
          cols_end--;
        }
        if (cols_start <= cols_end)
        {
          for (int i = cols_end; i >= cols_start; i--)
          {
            matrix[rows_start][i] += increment;
            increment++;
          }
          rows_start++;
        }
        if (rows_start <= rows_end)
        {
          for (int i = rows_start; i <= rows_end; i++)
          {
            matrix[i][cols_start] += increment;
            increment++;
          }
          cols_start++;
        }
      }
      std::ofstream file_output(name_output);
      if (!file_output.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      file_output << rows << " " << cols;
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          file_output << " " << matrix[i][j];
        }
      }
      file_output.close();
    }
    if (variant == variant_heap)
    {
      std::ifstream file_input(name_input);
      if (!file_input.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      if (file_input.peek() == std::ifstream::traits_type::eof())
      {
        std::cerr << "File is empty";
        return invalid_elements_in_file;
      }
      int rows = 0;
      int cols = 0;
      if (!(file_input >> rows) || !(file_input >> cols))
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      if (rows < 0 || cols < 0)
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      int** matrix = nullptr;
      try
      {
        matrix = createMatrix(rows, cols);
      }
      catch (const std::bad_alloc&)
      {
        std::cerr << "Matrix can not create";
        return invalid_elements_in_file;
      }
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          int x = 0;
          if (!(file_input >> x))
          {
            std::cerr << "Incorrect element in file";
            deleteMatrix(matrix, rows);
            return invalid_elements_in_file;
          }
          matrix[i][j] = x;
        }
      }
      file_input.close();
      if (rows == 0 || cols == 0)
      {
        std::ofstream file_output(name_output);
        if (!file_output.is_open())
        {
          std::cerr << "File can not open";
          deleteMatrix(matrix, rows);
          return invalid_elements_in_file;
        }
        file_output << rows << " " << cols;
        file_output.close();
        deleteMatrix(matrix, rows);
        return 0;
      }
      int rows_start = 0;
      int rows_end = rows - 1;
      int cols_start = 0;
      int cols_end = cols - 1;
      int increment = 1;
      while (rows_start <= rows_end && cols_start <= cols_end)
      {
        for (int i = cols_start; i <= cols_end; i++)
        {
          matrix[rows_end][i] += increment;
          increment++;
        }
        rows_end--;
        if (rows_start <= rows_end)
        {
          for (int i = rows_end; i >= rows_start; i--)
          {
            matrix[i][cols_end] += increment;
            increment++;
          }
          cols_end--;
        }
        if (cols_start <= cols_end)
        {
          for (int i = cols_end; i >= cols_start; i--)
          {
            matrix[rows_start][i] += increment;
            increment++;
          }
          rows_start++;
        }
        if (rows_start <= rows_end)
        {
          for (int i = rows_start; i <= rows_end; i++)
          {
            matrix[i][cols_start] += increment;
            increment++;
          }
          cols_start++;
        }
      }
      std::ofstream file_output(name_output);
      if (!file_output.is_open())
      {
        std::cerr << "File can not open";
        deleteMatrix(matrix, rows);
        return invalid_elements_in_file;
      }
      file_output << rows << " " << cols;
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          file_output << " " << matrix[i][j];
        }
      }
      deleteMatrix(matrix, rows);
      file_output.close();
    }
  }
  return 0;
}
