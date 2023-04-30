#ifndef SLAE_GMRES_H
#define SLAE_GMRES_H

#include "../Matrix/Vector.h"
#include "../Matrix/Sparce.h"
#include "../Matrix/Dense.h"
#include "Gaus_back.h"


template<typename T>
std::vector<std::vector<T>> ort_basis(const CSR<T> &A, const std::vector<T> &r, int m, Dense<T> &H) {
    std::vector<std::vector<T>> V(m + 1);
    std::vector<T> v = r / norm(r), t;
    T k = 0.25; // to evaluate whether nev vector's norm is much less, then others;
    V[0] = v;


    for (int i = 0; i < m; i++) {
        t = A * V[i];
        T tau = norm(t);
        for (int j = 0; j <= i; j++) {
            H(j, i) = scalar(V[j], t);
            t = t - V[j] * H(j, i);
        }
        if (norm(t) / tau <= k) {
            for (int j = 0; j <= i; j++) {
                T rho = scalar(V[j], t);
                t = t - V[j] * rho;
                H(j, i) += rho;
            }
        }
        H(i + 1, i) = norm(t);
        V[i + 1] = t / H(i + 1, i);
    }
    return V;
}

template<typename T>
std::vector<T> GMRES(const CSR<T> &A, const std::vector<T> b, const std::vector<T> x0, int m, T tolerance) {
    Dense<T> H_0(m + 1, m);
    std::vector<T> x = x0;
    std::vector<T> r = A * x - b;
    std::vector<std::vector<T>> V = ort_basis(A, r, m, H_0);
    std::vector<T> z(m);
    z[0] = 1;


    Dense<T> H = H_0;

        for (int i = 0; i < m; i++) {
            T sq = std::sqrt(H(i, i) * H(i, i) + H(i + 1, i) * H(i + 1, i));
            T cos = H(i, i) / sq;
            T sin = -H(i + 1, i) / sq;
            for (int j = 0; j < m; j++) {
                T a = cos * H(i, j) - sin * H(i + 1, j);
                T b = sin * H(i, j) + cos * H(i + 1, j);
                H(i, j) = a;
                H(i + 1, j) = b;
            }
            z[i] *= cos;
            if(i + 1 < m) z[i + 1] = std::pow(sin, i + 1);

            // writing H and z to storages with non-used rows
            std::vector<T> z_new(i + 1);
            Dense<T> H_new(i + 1, i + 1);
            for(int j = 0; j < i + 1; j ++) z_new[j] = z[j];
            for(int j = 0; j < i + 1; j ++)
                for(int u = 0; u < i + 1; u ++) H_new(j, u) = H(j, u);

            z_new = z_new * norm(r);
            std::vector<T> y = Gaus_back(H_new, z_new);
            x = x0;

            for(int j = 0; j < i + 1; j ++) x = x - V[j] * y[j];
            std::cout << norm(A * x - b) << "\n\n";
            if(stop_check(A, x, b, tolerance)) return x;
        }
    return x0;
}

#endif //SLAE_GMRES_H
