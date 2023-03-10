#include "gtest/gtest.h"
#include "../src/Decompositions/Householder.h"
#include <ctime>
#include <random>

TEST(HOUSEHOLDER, IS_ORTHOGONAL) {
    Dense<double> A{100, 50};
    std::srand(std::time(nullptr));
    for (int i = 0; i < 100; i++) for (int j = 0; j < 50; j++) A(i, j) = rand() % 1000;
    auto [Q, R] = Householder::QR(A);
    Dense<double> res_ = Q * Q.Transpose();
    //std::cout << A;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i == j) ASSERT_NEAR(res_(i, j), 1, 1e-10);
            else
                ASSERT_NEAR(res_(i, j), 0, 1e-10);
        }
    }
}

TEST(HOUSEHOLDER, DECOMPOSITION_SMALL) {
    Dense<double> A{5, 3, {12, -51, 4, 6, 167, -68, -4, 24, -41, -1, 1, 0, 2, 0, 3}};
    auto [Q, R] = Householder::QR(A);
    Dense<double> res_ = Q * R;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) ASSERT_NEAR(res_(i, j), A(i, j), 1e-10);
    }
}

TEST(HOUSEHOLDER, DECOMPOSITION_BIG) {
    Dense<double> A{100, 100};
    std::srand(std::time(nullptr));
    for (int i = 0; i < 100; i++) for (int j = 0; j < 100; j++) A(i, j) = rand();
    auto [Q, R] = Householder::QR(A);
    Dense<double> res_ = Q * R;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) ASSERT_NEAR(res_(i, j), A(i, j), 1e-3);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

