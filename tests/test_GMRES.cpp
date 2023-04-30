

#include <fstream>
#include <chrono>

#include "gtest/gtest.h"
#include "../src/Solvers/GMRES.h"
#include "txt_files/Matrix_gen.h"


TEST(GMRES, ORT_BASIS) {
    std::vector<double> b = b_20<double>();
    std::vector<double> x(20, 1);
    CSR<double> A = mat_20<double>();
    int n = 16, m = 15;
    std::vector<double> matrix_(n *m);
    Dense<double> H(n, m);
    std::vector<double> r = A * x - b;
    std::vector<std::vector<double>> V = ort_basis(A, r, m, H);
    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++) {
            ASSERT_NEAR(0, scalar(V[i], V[j]), 1e-4);
        }
    double tolerance = 1e-11;
    std::vector<double> res = GMRES(A, b, x, m, tolerance);
}

//TEST(GMRES, AV_is_equal_VH) {
//    std::vector<double> b = b_20<double>();
//    std::vector<double> x(20, 1);
//    CSR<double> A = mat_20<double>();
//    std::vector<double> matrix_(4 * 3);
//    Dense<double> H(4, 3);
//    std::vector<double> r = A * x - b;
//    std::vector<std::vector<double>> V1 = ort_basis(A, r, 3, H);
//    std::vector<std::vector<double>> V2 = ort_basis(A, r, 4, H);
//    //for(int i = 0; i < 20; i ++) std::cout <<
//
//}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
