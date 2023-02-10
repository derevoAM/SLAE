#include "gtest/gtest.h"
#include "TridiagonalMatrix_solver.h"

TEST(TRIDIAGONAL, INITIALIZATION) {
    std::initializer_list<double> in_list{4, 3, 2, 6, 7, 8, 5, 6, 4, 3.2, 2, 1, -2.9, 3, 4, 5, 6, 7, 8};
    TridiagonalMatrix<double> matrix_{in_list};

    int i = 0, j = 0;
    for (auto it: in_list) {
        ASSERT_TRUE(matrix_(i, j) == it) << matrix_(i, j) << " " << it << "\n";
        if (j == i + 1) {
            i += 1;
            j -= 1;
        } else j += 1;
    }
}

TEST(TRIDIAGONAL, SOLVE_1) {
    std::vector<double> coef_{3, 2, 5};
    TridiagonalMatrix<double> matrix_{2, 7, 1, -4, 9, 12, -6};
    std::vector<double> x = solver(matrix_, coef_);
    ASSERT_NEAR(x[0], -1.16666667, 1e-6);
    ASSERT_NEAR(x[1], 0.7619047, 1e-6);
    ASSERT_NEAR(x[2], 0.6904761, 1e-6);
}

TEST(TRIDIAGONAL, SOLVE_2) {
    std::vector<double> coef_{2.1, -23, 2.321, 1675.221, 31.9, 3, 2, 0.003};
    TridiagonalMatrix<double> matrix_{0.4, 6, 3.5, 231, 4432, 11.212, 231.3, -1.2, -243122.2, 21, 3, 111, 24.1, -21,
                                      8.3, 3, 2, 2, 32.1, 1, -12, -2};
    std::vector<double> x = solver(matrix_, coef_);
    ASSERT_NEAR(x[0], 6.063449699, 1e-9);
    ASSERT_NEAR(x[1], -0.054229980, 1e-9);
    ASSERT_NEAR(x[2], -0.007151387, 1e-9);
    ASSERT_NEAR(x[3], -3.819285351, 1e-9);
    ASSERT_NEAR(x[4], 5.588325148, 1e-9);
    ASSERT_NEAR(x[5], -15.293430375, 1e-9);
    ASSERT_NEAR(x[6], 1.248596197, 1e-9);
    ASSERT_NEAR(x[7], -7.493077184, 1e-9);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

