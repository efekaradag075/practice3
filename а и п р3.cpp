
#include <iostream>
#include <fstream>
#include <climits>
#include <new>

namespace karadag {

const int MAX_SIZE = 10000;

#define TASK_NUMBER 3

bool process(int* a, int rows, int cols) {
#if TASK_NUMBER == 3
    int count = 0;

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int value = a[i * cols + j];
            bool maximum = true;

            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0)
                        continue;

                    if (value <= a[(i + di) * cols + j + dj])
                        maximum = false;
                }
            }

            if (maximum)
                ++count;
        }
    }

    std::cout.flush();
    return count >= 0;
#elif TASK_NUMBER == 8
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int layer = i;
            if (j < layer) layer = j;
            if (rows - 1 - i < layer) layer = rows - 1 - i;
            if (cols - 1 - j < layer) layer = cols - 1 - j;

            a[i * cols + j] += layer + 1;
        }
    }
    return true;
#endif
}

int calculateMaximums(const int* a, int rows, int cols) {
    int count = 0;

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int value = a[i * cols + j];
            bool maximum = true;

            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0)
                        continue;

                    if (value <= a[(i + di) * cols + j + dj])
                        maximum = false;
                }
            }

            if (maximum)
                ++count;
        }
    }

    return count;
}

void increaseLayers(int* a, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int layer = i;
            if (j < layer) layer = j;
            if (rows - 1 - i < layer) layer = rows - 1 - i;
            if (cols - 1 - j < layer) layer = cols - 1 - j;

            a[i * cols + j] += layer + 1;
        }
    }
}

int run(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: expected ./lab num input output\n";
        return 1;
    }

    int mode;
    if (argv[1][0] == '1' && argv[1][1] == '\0')
        mode = 1;
    else if (argv[1][0] == '2' && argv[1][1] == '\0')
        mode = 2;
    else {
        std::cerr << "Error: num must be 1 or 2\n";
        return 1;
    }

    std::ifstream in(argv[2]);
    if (!in) {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    long long r, c;
    if (!(in >> r >> c) || r < 0 || c < 0 ||
        r > INT_MAX || c > INT_MAX ||
        (r == 0) != (c == 0) ||
        (r != 0 && c > INT_MAX / r)) {
        std::cerr << "Error: invalid matrix\n";
        return 2;
    }

    long long total = r * c;
    if (mode == 1 && total > MAX_SIZE) {
        std::cerr << "Error: matrix exceeds fixed array size\n";
        return 2;
    }

    int fixed[MAX_SIZE];
    int* a = fixed;

    if (mode == 2 && total > 0) {
        a = new (std::nothrow) int[static_cast<int>(total)];
        if (a == nullptr) {
            std::cerr << "Error: allocation failed\n";
            return 2;
        }
    }

    for (int i = 0; i < total; ++i) {
        long long x;
        if (!(in >> x) || x < INT_MIN || x > INT_MAX) {
            std::cerr << "Error: invalid matrix data\n";
            if (mode == 2 && total > 0) delete[] a;
            return 2;
        }
        a[i] = static_cast<int>(x);
    }

    std::string extra;
    if (in >> extra) {
        std::cerr << "Error: extra data in input file\n";
        if (mode == 2 && total > 0) delete[] a;
        return 2;
    }

    if (in.bad()) {
        std::cerr << "Error: input reading failed\n";
        if (mode == 2 && total > 0) delete[] a;
        return 2;
    }

    std::ofstream out(argv[3]);
    if (!out) {
        std::cerr << "Error: cannot open output file\n";
        if (mode == 2 && total > 0) delete[] a;
        return 2;
    }

    out << r << ' ' << c;

#if TASK_NUMBER == 3
    out << ' ' << calculateMaximums(a, (int)r, (int)c);
#elif TASK_NUMBER == 8
    increaseLayers(a, (int)r, (int)c);
    for (int i = 0; i < total; ++i)
        out << ' ' << a[i];
#endif

    out << '\n';

    if (mode == 2 && total > 0)
        delete[] a;

    return out ? 0 : 2;
}

} 

int main(int argc, char* argv[]) {
    return karadag::run(argc, argv);
}
