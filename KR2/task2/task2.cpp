#include <fstream>
#include <chrono>

#include "../../src/Matrix/Sparce.h"
#include "../../src/Solvers/FPI.h"
#include "../../src/Solvers/Conjugate_Gradient.h"
#include "../../src/Solvers/Gaus_Zeidel.h"
#include "../../src/Solvers/SOR_SSOR.h"
#include "../../src/Solvers/Gradient_Descent.h"
#include "../../src/Solvers/Conjugate_Gradient.h"







CSR<double> Gen_mat()
{
    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 18});
    dok_.push_back({1, 1, 21});
    dok_.push_back({2, 2, 24});
    dok_.push_back({3, 3, 27});
    return CSR<double>{dok_, 4, 4};
}


int main()
{
    CSR<double> A = Gen_mat();
    std::vector<double> b(4, 2);
    double c = 5;
    std::vector<double> x0(4, static_cast<double>(0));
    double t = 1e-13;

    double lam_max = 27.0;
    double lam_min = 18.0;

    std::vector<double> res_1 = FPI(A, b, x0, t, 1.8 / lam_max);
    double min_1 = scalar(res_1, A * res_1) - scalar(res_1, b) + c;
    std::cout << min_1 << "\n";

    std::vector<double> res_2 = FPI(A, b, x0, t, 2 / (lam_max + lam_min));
    double min_2 = scalar(res_2, A * res_2) - scalar(res_2, b) + c;
    std::cout << min_2 << "\n";

    std::vector<double> res_3 = Gradient_descent_fast(A, b, x0, t);
    double min_3 = scalar(res_3, A * res_3) - scalar(res_3, b) + c;
    std::cout << min_3 << "\n";

    std::vector<double> res_4 = FPI_Chebyshev_accelerated(A, b, x0, t, lam_max, lam_min, 8);
    double min_4 = scalar(res_4, A * res_4) - scalar(res_4, b) + c;
    std::cout << min_4 << "\n";

    std::vector<double> res_5 = Conjaguate_Gradient(A, b, x0, t);
    double min_5 = scalar(res_5, A * res_5) - scalar(res_5, b) + c;
    std::cout << min_5 << "\n";






}