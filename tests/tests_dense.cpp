#include "gtest/gtest.h"
#include "../src/Matrix/Dense.h"

TEST(DENSE, MULTIPLICATION) {
    Dense<double> matrix_{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    Dense<double> false_{3, 1, {1, 2, 3}};
    Dense<double> vec_{4, 2, {1, 5, 2, 6, 3, 7, 4, 8}};
    Dense<double> res_ = matrix_ * vec_;
    std::vector<double> answ_{30, 70, 70, 174, 110, 278};
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) ASSERT_TRUE(res_(i, j) == answ_[i * 2 + j]);


}

TEST(DENSE, ADDITION) {
    Dense<double> mat_1_{3, 2, {1, 2, 3, 4, 5, 6}};
    Dense<double> mat_2_{3, 2, {6, 5, 4, 3, 2, 1}};
    Dense<double> res_ = mat_1_ + mat_2_;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) ASSERT_TRUE(res_(i, j) == 7);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

