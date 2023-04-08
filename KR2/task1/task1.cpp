#include <fstream>
#include <chrono>

#include "../../src/Matrix/Sparce.h"
#include "../../src/Solvers/FPI.h"
#include "../../src/Solvers/Conjugate_Gradient.h"
#include "../../src/Solvers/Gaus_Zeidel.h"
#include "../../src/Solvers/SOR_SSOR.h"





CSR<double> Gen_mat(double a, double b)
{
    std::vector<DOK<double>> dok_;
    for(int i = 0; i < 289; i ++)
    {
        dok_.push_back({i, i, 2 * b});
    }

    for(int i = 0; i < 288; i ++)
    {
        dok_.push_back({i + 1, i, a});
        dok_.push_back({i, i + 1, a});
    }

    for(int i = 0; i < 272; i ++)
    {
        dok_.push_back({i + 17, i, a});
        dok_.push_back({i, i + 17, a});
    }

    return CSR<double>{dok_, 289, 289};
}






int main()
{
    double b = 18;
    double a = 6;
    CSR<double> A = Gen_mat(a, b);
    double lam_max = 59.82;
    double lam_min = 12.18;
    std::vector<double> c(289, static_cast<double>(3));
    std::vector<double> x0(289, static_cast<double>(0));
    double t = 1e-13;


    std::vector<double> res_1 = FPI(A, c, x0, t, 1 / lam_max);
    std::vector<double> res_2 = FPI(A, c, x0, t, 2 / (lam_max + lam_min));
    std::vector<double> res_3 = FPI_Chebyshev_accelerated(A, c, x0, t, lam_max, lam_min, 8);
    std::vector<double> res_4 = SSOR(A, c, x0, t, 1.02);

    std::ofstream out;
    out.open("speed1");

    double i = -10;
    while(i < 800)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<double> res_5 = FPI_Chebyshev_accelerated(A, c, x0, t, lam_max  + i, lam_min, 8);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        out << duration.count() << "\n";

        i += 0.5;
    }
    out.close();

}