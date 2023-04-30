#ifndef SLAE_GAUS_BACK_H
#define SLAE_GAUS_BACK_H

#include "../Matrix/Dense.h"

template<typename T>
std::vector<T> Gaus_back(const Dense<T> &A, const std::vector<T> &b) {
    int n = b.size();
    std::vector<T> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = 0; j < n - 1 - i; j++) {
            sum -= A(i, i + 1 + j) * x[i + 1 + j];
        }
        x[i] = sum / A(i, i);
        //std::cout << sum << "\n";
    }
    return x;
}

#endif //SLAE_GAUS_BACK_H
