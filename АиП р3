
#include <iostream>
#include <fstream>
#include <new>

namespace karadag
{
    int solve(const int* matrix, int rows, int cols)
    {
        if (rows == 0 || cols == 0)
        {
            return 0;
        }

        int bestRow = 0;
        int bestLength = 0;

        for (int i = 0; i < rows; ++i)
        {
            int currentLength = 1;

            for (int j = 1; j < cols; ++j)
            {
                if (matrix[i * cols + j] ==
                    matrix[i * cols + j - 1])
                {
                    ++currentLength;
                }
                else
                {
                    currentLength = 1;
                }

                if (currentLength > bestLength)
                {
                    bestLength = currentLength;
                    bestRow = i;
                }
            }
        }

        return bestRow + 1;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Error: expected 3 arguments\n";
        return 1;
    }

    int mode = -1;

    if (argv[1][0] == '1' && argv[1][1] == '\0')
        mode = 1;
    else if (argv[1][0] == '2' && argv[1][1] == '\0')
        mode = 2;
    else
    {
        std::cerr << "Error: mode must be 1 or 2\n";
        return 1;
    }

    std::ifstream input(argv[2]);

    if (!input)
    {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    int rows, cols;

    if (!(input >> rows >> cols) ||
        rows < 0 || cols < 0 ||
        ((rows == 0) != (cols == 0)) ||
        static_cast<long long>(rows) * cols > 2147483647LL)
    {
        std::cerr << "Error: invalid matrix dimensions\n";
        return 2;
    }

    long long count =
        static_cast<long long>(rows) * cols;

    int fixedMatrix[10000];
    int* matrix = fixedMatrix;

    if (mode == 1 && count > 10000)
    {
        std::cerr << "Error: matrix is too large\n";
        return 2;
    }

    if (mode == 2)
    {
        matrix = new (std::nothrow) int[
            count > 0 ? static_cast<int>(count) : 1
        ];

        if (matrix == nullptr)
        {
            std::cerr << "Error: memory allocation failed\n";
            return 2;
        }
    }

    for (long long i = 0; i < count; ++i)
    {
        if (!(input >> matrix[i]))
        {
            std::cerr << "Error: invalid matrix data\n";

            if (mode == 2)
                delete[] matrix;

            return 2;
        }
    }

    int result = karadag::solve(matrix, rows, cols);

    std::ofstream output(argv[3]);

    if (!output)
    {
        std::cerr << "Error: cannot open output file\n";

        if (mode == 2)
            delete[] matrix;

        return 2;
    }

    output << result << '\n';

    if (mode == 2)
        delete[] matrix;

    return 0;
}
