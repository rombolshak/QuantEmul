#include <gtest/gtest.h>
#include "../quantumstate.h"
#include "../Eigen/Core"


TEST(QuantumStateTest, TestConstructWithMatrix) {
    Eigen::Matrix4cd matr;
    matr(0,0) = matr(3,0) = matr(0,3) = matr(3,3) = 0.5;
    
    QuantumState state(matr);
    
    EXPECT_EQ(matr, state.densityMatrix());
}

TEST(QuantumStateTest, TestConstructWithVector) {
    Vector4cd vecCol(1, 1, 2, 3);
    Matrix<std::complex< double >, 1, 4> vecRow(1, 1, 2, 3);
    Matrix4cd res = vecCol * vecRow;
        
    QuantumState state(vecCol);
    
    EXPECT_EQ(res, state.densityMatrix());
}

TEST(QuantumStateTest, TestConstructWithNonSquareMatrixIsDisallowed) {
    Matrix<std::complex< double >, 2, 3> matr;
    matr.setConstant(0.9);
    
    EXPECT_ANY_THROW(QuantumState state(matr));
}

TEST(QuantumStateTest, TestConstructWithMatrixThatIsNotDensityMatrix) {
    MatrixXcd matr(3, 3);
    matr.setConstant(std::complex< double >(0.15, 1));
    
    EXPECT_ANY_THROW(QuantumState state(matr));
}