#include <gtest/gtest.h>
#include "../unitary_transformation.h"
#include "../hilbert_space.h"
#include "../Eigen/Dense"
#include "../quantum_state.h"

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
    HilbertSpace space(2);
    
    UnitaryTransformation ut(oldBasis, newBasis, space);
    
    EXPECT_EQ(true, resMatr.isApprox(ut.transformMatrix()));
}

TEST(UnitaryTransformationTest, TestConstructWithNonSquareBasisMatrix) {
    MatrixXcd oldBasis(2, 3), newBasis(2, 2);
    oldBasis.setRandom(); newBasis.setRandom();
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis, space));
    
    MatrixXcd temp = oldBasis;
    oldBasis = newBasis;
    newBasis = temp;
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis, space));
}

TEST(UnitaryTransformationTest, TestConstructWithDifferentSizeMatrices) {
    MatrixXcd oldBasis(2,2), newBasis(3,3);
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(oldBasis, newBasis, space));
}

TEST(UnitaryTransformationTest, TestConstructWithMatrix) {
    MatrixXcd matr(2,2);
    matr << 1, 0, 0, 1;
    HilbertSpace space(2);
    
    UnitaryTransformation ut(matr, space);
    
    EXPECT_EQ(matr, ut.transformMatrix());
}

TEST(UnitaryTransformationTest, TestConstructWithNonSquareMatrix) {
    MatrixXcd matr(2, 3);
    matr << 1,2,3,4,5,6;
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(UnitaryTransformation ut(matr, space));
}

TEST(UnitaryTransformationTest, TestConstructWithNonUnitaryMatrix) {
    MatrixXcd matr(2,2);
    matr << 1,1,1,1;
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(UnitaryTransformation(matr, space));
}

TEST(UnitaryTransformationTest, TestConstructWithWrongSpace) {
    MatrixXcd matr(2, 2);
    matr.setIdentity();
    HilbertSpace space(3);
    
    EXPECT_ANY_THROW(UnitaryTransformation(matr, space));
}

TEST(UnitaryTransformationTest, TestApplyingHadamardTransform) {
    MatrixXcd transformMatr(2,2), stateMatr(2,2), resMatr(2,2);
    transformMatr << 1,1,1,-1; transformMatr /= sqrt(2);
    stateMatr.setConstant(0.5);
    resMatr << 1,0,0,0;
    HilbertSpace space(2);
    QuantumState state(stateMatr, space);
    UnitaryTransformation ut(transformMatr, space);
    
    ut.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(resMatr));
}

TEST(UnitaryTransformationTest, TestApplyingWithDifferentStateAndTransformSpaceDimensions) {
    MatrixXcd transformMatr(4,4), stateMatr(4,4);    
    transformMatr.setIdentity();
    stateMatr.setConstant(0);
    stateMatr(0,0) = stateMatr(0,3) = stateMatr(3,0) = stateMatr(3,3) = 0.5;
    
    std::vector<uint> dims; dims.push_back(2); dims.push_back(2);;
    HilbertSpace space4(4);
    HilbertSpace space2x2(dims);
    QuantumState state(stateMatr, space4);
    UnitaryTransformation ut(transformMatr, space2x2);
    
    EXPECT_ANY_THROW(ut.applyTo(&state));
}
