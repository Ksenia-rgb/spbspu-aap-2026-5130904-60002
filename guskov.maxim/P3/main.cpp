#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc == 2)
    {
        std::cerr << "Not enough arguments\n";
        return 1;
    }
    if (argc > 4)
    {
        std::cerr << "Too many arguments\n";
        return 1;
    }
    if (argc == 2)
    {
        std::cerr << "Not enough arguments\n";
        return 1;
    }
    
    std::ifstream in(argv[2]);
    if (!in)
    {
        std::cerr << "Can't open input file: " << argv[2] << '\n';
        return 1;
    }

    std::ofstream out(argv[3]);
    if (!out)
    {
        std::cerr << "Can't open output file: " << argv[3] << '\n';
        return 1;
    }

    int rows;
    int cols;
    const int MAX_COLS = 10000; 

    in >> rows >> cols;
    int count = cols;
    if (num == 1)
    {
        int arr[MAX_COLS];
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                in >> arr[j];
            }

            for (int j = 1; j < cols; ++j)
            {
                if (arr[j] == arr[j - 1])
                {
                    --count;
                    break;
                }
            }
        }
    }
    if (num == 2)
    {
        int** matrix = new int*[rows];
        for (int i=0;i < rows; ++i)
        {
            matrix[i] = new int[cols];
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                in >> matrix[i][j];
            }
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                if (matrix[i][j] == matrix[i][j - 1])
                {
                    --count;
                    break;
                }
            }
        }
        

        for (int i=0;i < cols; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    

    out  << count << "\n";
    return 0;
}
