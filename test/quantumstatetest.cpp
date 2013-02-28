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
    Vector4cd vecCol(1/sqrt(2), 0, 0, 1/sqrt(2));
    Matrix<std::complex< double >, 1, 4> vecRow(1/sqrt(2), 0, 0, 1/sqrt(2));
    Matrix4cd res = vecCol * vecRow;
        
    HilbertSpace space(4);
    QuantumState state(vecCol, space);
    
    EXPECT_EQ(res, state.densityMatrix());
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