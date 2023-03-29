#include <fstream>

#include "gtest/gtest.h"
#include "../src/Solvers/Gaus_Zeidel.h"
#include "../src/Solvers/Jacobi.h"
#include "../src/Solvers/FPI.h"
#include "../src/Solvers/SOR.h"


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
    for (int i = 0; i < 2; i++) ASSERT_NEAR(diff_[i], 0, 1e-3);
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

TEST(ITTERATIONS, SOR) {
    std::vector<DOK<double>> dok_;

    std::string line;
    std::string i_;
    std::string j_;
    std::string value_;

    std::ifstream file("/home/derevo/Projects/SLAE/tests/txt_files/mat_diag_pos_20.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[1] == ' ') {
                i_.assign(line, 0, 1);
                line.erase(0, 2);
            } else {
                i_.assign(line, 0, 2);
                line.erase(0, 3);
            }

            if (line[1] == ' ') {
                j_.assign(line, 0, 1);
                line.erase(0, 2);
            } else {
                j_.assign(line, 0, 2);
                line.erase(0, 3);
            }

            value_ = line;
            dok_.push_back({std::stoi(i_), std::stoi(j_), std::stod(value_)});
        }
    }
    file.close();

    std::vector<double> b;
    b.reserve(20);

    std::ifstream file_b("/home/derevo/Projects/SLAE/tests/txt_files/b_20.txt");
    if (file_b.is_open()) {
        while (getline(file_b, line)) {
            b.push_back(std::stod(line));
        }
    }
    file_b.close();
    std::vector<double> x(20, 1);
    CSR<double> A(dok_, 20, 20);

    std::vector<DOK<double>> dok_diag;
    std::vector<DOK<double>> dok_unit;


    for (int i = 0; i < 20; i++) {
        dok_diag.push_back({i, i, 1 / A(i, i)});
        dok_unit.push_back({i, i, 1});
        //A(i, i) = A(i, i) * 300;
    }

    CSR<double> D(dok_diag, 20, 20);
    CSR<double> E(dok_unit, 20, 20);

    E = E - D * A;
    double w = abs(E.max_eigenvalue_pow());
    w = 1 + (w / (1 + sqrt(1 - w * w))) * (w / (1 + sqrt(1 - w * w)));
    double t = 1e-7;


    std::vector<double> res_ = SOR(A, b, x, t, w);
    std::vector<double> diff_ = A * res_ - b;
    for (int i = 0; i < 20; i++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
