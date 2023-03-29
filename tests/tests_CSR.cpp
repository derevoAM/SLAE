#include "gtest/gtest.h"
#include "../src/Matrix/Sparce.h"

TEST(SRC, INITIALIZATION_RANDOM) {
    std::vector<DOK<double>> dok_;
    dok_.push_back({2, 2, 50});
    dok_.push_back({2, 3, 60});
    dok_.push_back({0, 1, 20});
    dok_.push_back({1, 1, 30});
    dok_.push_back({1, 3, 40});
    dok_.push_back({0, 0, 10});
    CSR<double> matrix_(dok_, 3, 4);

    int test_matrix_[3][4];
    test_matrix_[0][0] = 10;
    test_matrix_[0][1] = 20;
    test_matrix_[0][2] = 0;
    test_matrix_[0][3] = 0;
    test_matrix_[1][0] = 0;
    test_matrix_[1][1] = 30;
    test_matrix_[1][2] = 0;
    test_matrix_[1][3] = 40;
    test_matrix_[2][0] = 0;
    test_matrix_[2][1] = 0;
    test_matrix_[2][2] = 50;
    test_matrix_[2][3] = 60;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) ASSERT_TRUE(test_matrix_[i][j] == matrix_(i, j));


}

TEST(SRC, ZERO_INITIALIZATION) {
    std::vector<DOK<double>> dok_;
    CSR<double> matrix_(dok_, 3, 4);
    for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) ASSERT_TRUE(matrix_(i, j) == 0);
}

TEST(SRC, ZERO_ROW) {
    std::vector<DOK<double>> dok_;
    dok_.push_back({2, 2, 50});
    dok_.push_back({2, 3, 60});
    dok_.push_back({0, 1, 20});
    dok_.push_back({0, 0, 10});
    CSR<double> matrix_(dok_, 3, 4);

    int test_matrix_[3][4];
    test_matrix_[0][0] = 10;
    test_matrix_[0][1] = 20;
    test_matrix_[0][2] = 0;
    test_matrix_[0][3] = 0;
    test_matrix_[1][0] = 0;
    test_matrix_[1][1] = 0;
    test_matrix_[1][2] = 0;
    test_matrix_[1][3] = 0;
    test_matrix_[2][0] = 0;
    test_matrix_[2][1] = 0;
    test_matrix_[2][2] = 50;
    test_matrix_[2][3] = 60;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) ASSERT_TRUE(test_matrix_[i][j] == matrix_(i, j));

}

TEST(SRC, ORDER) {
    std::vector<DOK<double>> dok_;
    dok_.push_back({2, 2, 50});
    dok_.push_back({2, 3, 60});
    dok_.push_back({0, 1, 20});
    dok_.push_back({1, 1, 30});
    dok_.push_back({1, 3, 40});
    dok_.push_back({0, 0, 10});
    CSR<double> matrix_(dok_, 3, 4);

    std::vector<double> value{10, 20, 30, 40, 50, 60};
    std::vector<int> column{0, 1, 1, 3, 2, 3};
    std::vector<int> row{0, 2, 4, 6};
    for (int i = 0; i < 6; i++) {
        ASSERT_TRUE(value[i] == matrix_.get_value(i));
        ASSERT_TRUE(column[i] == matrix_.get_col(i));
        if (i < 4) ASSERT_TRUE(row[i] == matrix_.get_row(i));
    }
}

TEST(SRC, MULTIPLICATION) {
    std::vector<DOK<double>> dok_;
    dok_.push_back({2, 2, 50});
    dok_.push_back({2, 3, 60});
    dok_.push_back({0, 1, 20});
    dok_.push_back({1, 1, 30});
    dok_.push_back({1, 3, 40});
    dok_.push_back({0, 0, 10});
    CSR<double> matrix_(dok_, 3, 4);
    std::vector<double> multip_{3, 2, 55, 1};
    std::vector<double> answer_{70, 100, 2810};
    std::vector<double> result_ = matrix_ * multip_;
    for (int i = 0; i < 3; i++) ASSERT_TRUE(answer_[i] == result_[i]);

}

TEST(SRC, MAX_EIGENVALUE) {
    std::vector<DOK<double>> dok_;
    dok_.push_back({2, 2, 2.45});
    dok_.push_back({2, 1, 6.6});
    dok_.push_back({0, 1, 2.1});
    dok_.push_back({1, 1, -1.2});
    dok_.push_back({1, 2, 4});
    dok_.push_back({0, 0, -13.2});
    dok_.push_back({2, 3, -12});
    dok_.push_back({3, 3, 0.3});
    dok_.push_back({0, 3, 1.1});

    CSR<double> matrix_(dok_, 4, 4);
    matrix_ = matrix_ * matrix_.transpose();
    double lambda = matrix_.max_eigenvalue_pow(1e-5);

}

TEST(SRC, MAX_EIGENVALUE_SOR) {
    std::vector<DOK<double>> dok_;

    dok_.push_back({0, 0, 2.45});
    dok_.push_back({1, 0, -2});
    dok_.push_back({2, 0, 3.2});
    dok_.push_back({3, 0, 6.7});
    dok_.push_back({1, 1, 3.4});
    dok_.push_back({1, 2, -1.23});
    dok_.push_back({1, 3, 2.45});
    dok_.push_back({2, 2, 0.5});
    dok_.push_back({2, 3, 1.45});
    dok_.push_back({3, 3, 8});
    CSR<double> matrix_(dok_, 4, 4);
    matrix_ = matrix_ * matrix_.transpose();


    std::vector<DOK<double>> diag;
    diag.push_back({0, 0, 400.0/2401});
    diag.push_back({1, 1, 25.0/389});
    diag.push_back({2, 2, 10000.0/120029});
    diag.push_back({3, 3, 200.0/23399});
    CSR<double> diag_(diag, 4, 4);

    std::vector<DOK<double>> unit;
    unit.push_back({0, 0, 1});
    unit.push_back({1, 1, 1});
    unit.push_back({2, 2, 1});
    unit.push_back({3, 3, 1});
    CSR<double> unit_(unit, 4, 4);

    matrix_ = unit_ - (diag_ * matrix_);
    double lambda = matrix_.max_eigenvalue_pow(1e-5);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

