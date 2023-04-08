#ifndef SLAE_CONJUGATE_GRADIENT_H
#define SLAE_CONJUGATE_GRADIENT_H

#include <fstream>
#include "../Matrix/Sparce.h"

template<typename T>
std::vector<T> Conjaguate_Gradient(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance)
{
    std::vector<T> x = x0;
    std::vector<T> r = A * x - b, r1;
    std::vector<T> d = r;
    T a, beta;
    int count = 0;

    std::ofstream out;
    out.open("descent");
    out << 0 << " " << 0 << "\n";

    while(!stop_check(A, x, b, tolerance))
    {
        a = scalar(d, r) / scalar(d, A * d);
        x = x - d * a;
        r1 = A * x - b;
        beta = scalar(r1, r1) / scalar(r, r);
        r = r1;
        d = r1 + d * beta;
        count ++;
        out << x[0] << " " << x[3] << "\n";
    }
    return x;
}


#endif //SLAE_CONJUGATE_GRADIENT_H
