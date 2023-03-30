#ifndef SLAE_JACOBI_H
#define SLAE_JACOBI_H

#include "../Matrix/Sparce.h"

template<typename T>
std::vector<T> Jacobi(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance) {
    std::vector<T> x = x0;
    std::vector x_1 = x;
    while (!stop_check(A, x_1, b, tolerance)) {
        x = x_1;

        x_1 = b - A * x;
        for (int i = 0; i < x.size(); i++) {
            x_1[i] = (x_1[i] + A(i, i) * x[i]) / A(i, i);
        }

    }
    return x_1;
}

#endif //SLAE_JACOBI_H
