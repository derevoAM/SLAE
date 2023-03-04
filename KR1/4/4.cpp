#include "../../src/Solvers/Gaus_Zeidel.h"
#include "../../src/Solvers/Jacobi.h"
#include "../../src/Solvers/FPI.h"
#include <fstream>

int main()
{
    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 12});
    dok_.push_back({0, 1, 17});
    dok_.push_back({0, 2, 3});
    dok_.push_back({1, 0, 17});
    dok_.push_back({1, 1, 15825});
    dok_.push_back({1, 2, 28});
    dok_.push_back({2, 0, 3});
    dok_.push_back({2, 1, 28});
    dok_.push_back({2, 2, 238});

    std::vector<double> b{1, 2, 3};
    std::vector<double> x{1, 1, 1};
    CSR<double> A(dok_, 3, 3);

    double t = 1e-20; // t делаю для каждого метода свой, так как, например, в мпи минимальная невязка гдето 20 порядка, а в остальных 30-го
    double tau = 1e-4;
    std::vector<double> gaus_ = Gaus_Zeidel(A, b, x, t);
    std::vector<double> jacobi_ = Jacobi(A, b, x, t);
    std::vector<double> fpi_ = FPI(A, b, x, t, tau);
    std::cout << gaus_ << "\n" << jacobi_ << "\n" << fpi_;
}