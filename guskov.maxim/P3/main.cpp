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

    in >> rows >> cols;
    int count = cols;
    
    out  << count << "\n";
    return 0;
}
