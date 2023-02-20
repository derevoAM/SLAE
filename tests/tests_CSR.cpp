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


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

