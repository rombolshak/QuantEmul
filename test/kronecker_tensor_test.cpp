#include <gtest/gtest.h>
#include <../kronecker_tensor.h>

TEST(KroneckerTensorTest, TestProduct) {
    Matrix2cd first, second;
    first << 1,2,3,4; second << 0,5,6,7;
    Matrix4cd res;
    res <<  0, 5, 0, 10,
	    6, 7, 12,14,
	    0, 15,0, 20,
	    18,21,24,28;
    
    EXPECT_EQ(res, KroneckerTensor::product(first, second));
}