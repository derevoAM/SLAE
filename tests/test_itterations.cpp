#include <fstream>
#include <chrono>

#include "gtest/gtest.h"
#include "../src/Solvers/Gaus_Zeidel.h"
#include "../src/Solvers/Jacobi.h"
#include "../src/Solvers/FPI.h"
#include "../src/Solvers/SOR_SSOR.h"
#include "../src/Utility/Gradient_Descent.h"
#include "../src/Solvers/Conjugate_Gradient.h"
#include "txt_files/Matrix_gen.h"


TEST(ITTERATIONS, GAUS_ZEIDEL) {
    std::vector<double> b = b_1000<double>();
    std::vector<double> x(1000, 1);
    CSR<double> A = mat_diag_pos_1000<double>();

    double t = 1e-25;
    double rho = 0.428;

//    auto start = std::chrono::high_resolution_clock::now();

    std::vector<double> res_ = Gaus_Zeidel_accelerated(A, b, x, rho, t);

//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << duration.count();
    std::vector<double> diff_ = A * res_ - b;
}

TEST(ITTERATIONS, JACOBI) {

    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 16});
    dok_.push_back({0, 1, 3});
    dok_.push_back({1, 0, 7});
    dok_.push_back({1, 1, -11});
    std::vector<double> b{11, 13};
    std::vector<double> x{1, 1};
    CSR<double> A(dok_, 2, 2);
    double t = 1e-7;
    std::vector<double> res_ = Jacobi(A, b, x, t);
    std::vector<double> diff_ = A * res_ - b;
    for (int i = 0; i < 2; i++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}

TEST(ITTERATIONS, FPI) {

    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 10});
    dok_.push_back({0, 1, -0.5});
    dok_.push_back({1, 0, -0.5});
    dok_.push_back({1, 1, 10});
    std::vector<double> b{1, 3};
    std::vector<double> x{1, 1};
    CSR<double> A(dok_, 2, 2);
    double t = 1e-7;
    double tau = 1e-2;
    std::vector<double> res_ = FPI(A, b, x, t, tau);
    std::vector<double> diff_ = A * res_ - b;
    for (int i = 0; i < 2; i++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}

TEST(ITTERATIONS, SOR_SSOR) {
    std::vector<double> b = b_100<double>();
    std::vector<double> x(100, 1);
    CSR<double> A = mat_diag_pos_100<double>();

    std::vector<DOK<double>> dok_diag;
    std::vector<DOK<double>> dok_unit;


    for (int i = 0; i < 100; i++) {
        dok_diag.push_back({i, i, 1 / A(i, i)});
        dok_unit.push_back({i, i, 1});
    }

    CSR<double> D(dok_diag, 100, 100);
    CSR<double> E(dok_unit, 100, 100);

    E = E - D * A;
    double w = abs(E.max_eigenvalue_pow());
    w = 1 + (w / (1 + sqrt(1 - w * w))) * (w / (1 + sqrt(1 - w * w)));
    double t = 1e-7;


    std::vector<double> res_ = SOR(A, b, x, t, w);
    std::vector<double> res_s = SSOR(A, b, x, t, w);

    std::vector<double> diff_ = A * res_ - b;
    std::vector<double> diff_s = A * res_s - b;
}

TEST(ITTERATIONS, MPI_CHEBYSHEV) {
    std::vector<double> b = b_20<double>();
    std::vector<double> x(20, 1);
    CSR<double> A = mat_diag_pos_20<double>();

    double t = 1e-25;
    double lam_min = 50.926;
    double lam_max = 768.68;

    std::vector<double> res_ = FPI_Chebyshev_accelerated(A, b, x, t, lam_max, lam_min, 64);
}


TEST(ITTERATIONS, GRADIENT_DESCENT) {
    std::vector<double> b = b_100<double>();
    std::vector<double> x(100, 1);
    CSR<double> A = mat_diag_pos_100<double>();
    double t = 1e-10;

    std::vector<double> res_ = Gradient_descent_fast(A, b, x, t);
}


TEST(ITTERATIONS, CONJUGATE_GRADIENT) {
    std::vector<double> b = b_1000<double>();
    std::vector<double> x(1000, 1);
    CSR<double> A = mat_diag_pos_1000<double>();
    double t = 1e-25;

    std::vector<double> res_ = Conjaguate_Gradient(A, b, x, t);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
