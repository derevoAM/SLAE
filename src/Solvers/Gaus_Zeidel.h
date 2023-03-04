#ifndef SLAE_GAUS_ZEIDEL_H
#define SLAE_GAUS_ZEIDEL_H

#include "../Matrix/Sparce.h"
#include "../Matrix/Vector.h"

template<typename T>
bool stop_check(CSR<T> &A, std::vector<T> &x, std::vector<T> &b, T tolerance) {
    std::vector<T> res_ = A * x - b;
    return norm(A * x - b) < tolerance;
}

template<typename T>
std::vector<T> Gaus_Zeidel(CSR<T> &A, std::vector<T> &b, std::vector<T> &x, T tolerance) {
    while (!stop_check(A, x, b, tolerance)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x[i] = sum / A(i, i);
        }

    }
    return x;
}

#endif //SLAE_GAUS_ZEIDEL_H