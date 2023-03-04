#include "../../src/Solvers/FPI.h"
#include <fstream>

int main() {
    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 10});
    dok_.push_back({0, 1, 1});
    dok_.push_back({0, 2, 0});
    dok_.push_back({1, 0, 1});
    dok_.push_back({1, 1, 7});
    dok_.push_back({1, 2, 0});
    dok_.push_back({2, 0, 0});
    dok_.push_back({2, 1, 0.1});
    dok_.push_back({2, 2, 1});

    std::vector<double> b{20, 30, 1};
    std::vector<double> x{0, 0, 0};
    double t = 1e-12;
    CSR<double> A(dok_, 3, 3);
    double tau = 1e-5;
    for(int i = 0; i < 100; i ++) {
        std::vector<double> fpi_ = FPI(A, b, x, t, tau);
        tau += 1e-5;
    }
}