#include <gtest/gtest.h>
#include "Eigen/Dense"

using Eigen::MatrixXd;

TEST(SomeTest, CheckTesting) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(EigenTest, CheckInclude) {
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    EXPECT_EQ(1.5, m(1,1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
