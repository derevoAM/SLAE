#ifndef SLAE_JACOBI_H
#define SLAE_JACOBI_H

#include "../Matrix/Sparce.h"

template<typename T>
std::vector<T> Jacobi(CSR<T> &A, std::vector<T> &b, std::vector<T> &x0, T tolerance) {
    std::vector<T> x = x0;
    std::ofstream fout;
    fout.open("jacobi.txt");
    int count = 1;
    std::vector x_1 = x;
    while (!stop_check(A, x_1, b, tolerance)) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x_1[i] = sum / A(i, i);
        }
        fout << norm(A * x_1 - b) << " " << count << "\n";
        count ++;

    }
    fout.close();
    return x_1;
}

#endif //SLAE_JACOBI_H
