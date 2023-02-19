#ifndef TRIDIAGONAL_MATRIX_TRIDIAGONALMATRIX_SOLVER_H
#define TRIDIAGONAL_MATRIX_TRIDIAGONALMATRIX_SOLVER_H

#include <vector>
#include "../Matrix/TridiagonalMatrix.h"

template<typename T>
std::vector<T> solver(const TridiagonalMatrix<T> &A, const std::vector<T> &d) {
    int n = A.Get_size();
    std::vector<T> x(n);
    std::vector<T> p;
    std::vector<T> q;

    p.reserve(n - 1);
    q.reserve(n - 1);
    p.push_back(-(A(0, 1)) / A(0, 0));
    q.push_back(d[0] / A(0, 0));

    for (int i = 1; i < n - 1; i++) {
        p.push_back(-A(i, i + 1) / (A(i, i) + A(i, i - 1) * p[i - 1]));
        q.push_back((d[i] - A(i, i - 1) * q[i - 1]) /
                    (A(i, i) + A(i, i - 1) * p[i - 1]));
    }

    x[n - 1] = (d[n - 1] - A(n - 1, n - 2) * q[n - 2]) /
               (A(n - 1, n - 1) + A(n - 1, n - 2) * p[n - 2]);
    for (int i = n - 2; i >= 0; i--) x[i] = p[i] * x[i + 1] + q[i];
    return x;
}

#endif //TRIDIAGONAL_MATRIX_TRIDIAGONALMATRIX_SOLVER_H
