#ifndef SLAE_SOR_SSOR_H
#define SLAE_SOR_SSOR_H

#include "../Matrix/Sparce.h"

template<typename T>
std::vector<T> SOR(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance, T w) {
    std::vector<T> x = x0;
    while (!stop_check(A, x, b, tolerance)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }
    }
    return x;
}

template<typename T>
std::vector<T> SSOR(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance, T w) {
    std::vector<T> x = x0;
    while (!stop_check(A, x, b, tolerance)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }

        for (int i = x.size() - 1; i > 0; i--) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }

    }
    return x;
}

#endif //SLAE_SOR_SSOR_H
