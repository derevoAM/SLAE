#include "gtest/gtest.h"
#include "../src/Matrix/Sparce.h"
#include "../src/Solvers/Gaus_Zeidel.h"
#include "../src/Solvers/Jacobi.h"

TEST(ITTERATIONS, GAUS_ZEIDEL) {

    std::vector<DOK<double>> dok_;
    dok_.push_back({0, 0, 16});
    dok_.push_back({0, 1, 3});
    dok_.push_back({1, 0, 7});
    dok_.push_back({1, 1, -11});
    std::vector<double> b{11, 13};
    std::vector<double> x{1, 1};
    CSR<double> A(dok_, 2, 2);
    double t = 1e-7;
    std::vector<double> res_ = Gaus_Zeidel(A, b, x, t);
    std::vector<double> diff_ = A * res_ - b;
    for(int i = 0; i < 2; i ++) ASSERT_NEAR(diff_[i], 0, 1e-3);
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
    for(int i = 0; i < 2; i ++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

