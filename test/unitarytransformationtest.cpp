#include <gtest/gtest.h>
#include "../unitarytransformation.h"
#include "../hilbertspace.h"
#include "../Eigen/Dense"

using namespace Eigen;

TEST(UnitaryTransformationTest, TestConstructWithBasises) {
    MatrixXcd oldBasis(2, 2), newBasis(2, 2);
    oldBasis << 1, 0, 0, 1; // { |0>, |1> }
    newBasis << 1, 1, 1, -1; // { 1/sqrt(2) * (|0> + |1>), 1/sqrt(2) * (|0> - |1>)
    // assume normalization will be done inside constructor
    
    Vector2cd vec1(1, 1); vec1.normalize();
    Vector2cd vec2(1, -1); vec2.normalize();
    Matrix2cd resMatr;
    resMatr.col(0) = vec1;
    resMatr.col(1) = vec2;
    
    UnitaryTransformation ut(oldBasis, newBasis);
    
    EXPECT_EQ(true, resMatr.isApprox(ut.transformMatrix()));
}

TEST(UnitaryTransformationTest, TestConstructWithNonSquareBasisMatrix) {
    MatrixXcd oldBasis(2, 3), newBasis(2, 2);
    oldBasis.setRandom(); newBasis.setRandom();
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis));
    
    MatrixXcd temp = oldBasis;
    oldBasis = newBasis;
    newBasis = temp;
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis));
}

TEST(UnitaryTransformationTest, TestConstructWithDifferentSizeMatrices) {
    MatrixXcd oldBasis(2,2), newBasis(3,3);
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis));
}