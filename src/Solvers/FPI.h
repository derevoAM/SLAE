#ifndef SLAE_FPI_H
#define SLAE_FPI_H

#include "../Matrix/Sparce.h"

template<typename T>
std::vector<T> FPI(CSR<T> &A, std::vector<T> &b, std::vector<T> &x0, T tolerance, T tau) {
    std::vector<T> x = x0;
    std::vector x_1 = x;
    std::ofstream fout;
    fout.open("fpi.txt");
    int count = 1;
    while (!stop_check(A, x_1, b, tolerance)) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x[i];
            for (int j = 0; j < x.size(); j++) sum -= x[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        fout << norm(A * x_1 - b) << " " << count << "\n";
        count ++;


    }
    fout.close();
    return x_1;
}

#endif //SLAE_FPI_H
