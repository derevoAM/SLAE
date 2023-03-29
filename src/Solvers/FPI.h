#ifndef SLAE_FPI_H
#define SLAE_FPI_H

#include "../Matrix/Sparce.h"
#include <chrono>

template<typename T>
std::vector<T> FPI(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance, T tau) {
    std::vector<T> x = x0;
    std::vector x_1 = x;
    while (!stop_check(A, x_1, b, tolerance)) {
        x = x_1;
        //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        x_1 = x - (A * x - b) * tau;
        //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    }
    return x_1;
}

#endif //SLAE_FPI_H
