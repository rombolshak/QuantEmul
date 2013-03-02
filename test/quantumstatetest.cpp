#include <gtest/gtest.h>
#include "../quantumstate.h"
#include "../Eigen/Core"
#include "../hilbertspace.h"


TEST(QuantumStateTest, TestConstructWithMatrix) {
    Matrix4cd matr;
    matr(0,0) = matr(3,0) = matr(0,3) = matr(3,3) = 0.5;
    
    HilbertSpace space(4);
    QuantumState state(matr, space);
    
    EXPECT_EQ(matr, state.densityMatrix());
}

TEST(QuantumStateTest, TestConstructWithVector) {
    Vector4cd vecCol(1, 1, 0, 1); vecCol.normalize();
    Matrix<std::complex< double >, 1, 4> vecRow(1, 1, 0, 1); vecRow.normalize();
    Matrix4cd res = vecCol * vecRow;
        
    HilbertSpace space(4);
    QuantumState state(vecCol, space);
    
    EXPECT_EQ(true, res.isApprox(state.densityMatrix()));
}

TEST(QuantumStateTest, TestConstructWithNonSquareMatrixIsDisallowed) {
    Matrix<std::complex< double >, 2, 3> matr;
    matr.setConstant(0.9);
        
    HilbertSpace space(4);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QuantumStateTest, TestConstructWithMatrixThatIsNotDensityMatrix) {
    MatrixXcd matr(3, 3);
    matr.setConstant(std::complex< double >(0.15, 1));
    
    HilbertSpace space(3);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QuantumStateTest, TestConstructWithWrongSpaceDimension) {
    Matrix4cd matr;
    matr(0,0) = matr(3,0) = matr(0,3) = matr(3,3) = 0.5;
    
    HilbertSpace space(5);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QuantumStateTest, TestConstructWithMatrixThatHasNegativeEigenValues) {
    Matrix2cd matr;
    matr << 0, 1, 1, 0;    
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QuantumStateTest, TestConstructWithMatrixThatHasNonUnitaryTrace) {
    Matrix2cd matr;
    matr << 1,1,1,1;
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QuantumStateTest, TestAutonormalizeVector) {
    Vector4cd vec(1,0,0,1);
    HilbertSpace space(4);
    
    QuantumState(vec, space);
}

TEST(QuantumStateTest, TestEigenDecomposition) {
    Matrix2cd matr;
    matr.setConstant(0.5);
    HilbertSpace space(2);
    
    QuantumState state(matr, space);
    Vector2d values(0, 1);
    Vector2cd vec1(-1, 1); vec1.normalize();
    Vector2cd vec2(1, 1); vec2.normalize();
    Matrix2cd vectors; // will contain eigen vectors vec1 and vec2 as columns
    vectors.block<1,2>(0,0) = vec1.transpose();
    vectors.block<1,2>(1,0) = vec2.transpose();
    
    EXPECT_EQ(true, values.isApprox(state.eigenValues()));
    EXPECT_EQ(true, vectors.isApprox(state.eigenVectors()));
}

TEST(QuantumStateTest, TestPureStateDetermination) {
    Matrix2cd matrPure, matrMixed;
    matrPure << 0.5, 0.5, 0.5, 0.5;
    matrMixed << 0.5, -0.25, -0.25, 0.5;
    HilbertSpace space(2);
    
    QuantumState pureState(matrPure, space), mixedState(matrMixed, space);
    
    EXPECT_EQ(true, pureState.isPure());
    EXPECT_EQ(false, mixedState.isPure());
}