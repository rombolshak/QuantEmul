#include <gtest/gtest.h>
#include "../quantum_state.h"
#include "../Eigen/Core"
#include "../hilbert_space.h"


TEST(QST, TestConstructWithMatrix) {
    Matrix4cd matr;
    matr(0,0) = matr(3,0) = matr(0,3) = matr(3,3) = 0.5;
    
    HilbertSpace space(4);
    QuantumState state(matr, space);
    
    EXPECT_EQ(matr, state.densityMatrix());
}

TEST(QST, TestConstructWithVector) {
    Vector4cd vecCol(1, 1, 0, 1); vecCol.normalize();
    Matrix<std::complex< double >, 1, 4> vecRow(1, 1, 0, 1); vecRow.normalize();
    Matrix4cd res = vecCol * vecRow;
        
    HilbertSpace space(4);
    QuantumState state(vecCol, space);
    
    EXPECT_EQ(true, res.isApprox(state.densityMatrix()));
}

TEST(QST, TestConstructWithNonSquareMatrixIsDisallowed) {
    Matrix<std::complex< double >, 2, 3> matr;
    matr.setConstant(0.9);
        
    HilbertSpace space(4);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QST, TestConstructWithMatrixThatIsNotDensityMatrix) {
    MatrixXcd matr(3, 3);
    matr.setConstant(std::complex< double >(0.15, 1));
    
    HilbertSpace space(3);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QST, TestConstructWithWrongSpaceDimension) {
    Matrix4cd matr;
    matr(0,0) = matr(3,0) = matr(0,3) = matr(3,3) = 0.5;
    
    HilbertSpace space(5);
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QST, TestConstructWithMatrixThatHasNegativeEigenValues) {
    Matrix2cd matr;
    matr << 0, 1, 1, 0;    
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QST, TestConstructWithMatrixThatHasNonUnitaryTrace) {
    Matrix2cd matr;
    matr << 1,1,1,1;
    HilbertSpace space(2);
    
    EXPECT_ANY_THROW(QuantumState state(matr, space));
}

TEST(QST, TestAutonormalizeVector) {
    Vector4cd vec(1,0,0,1);
    HilbertSpace space(4);
    
    QuantumState(vec, space);
}

TEST(QST, TestEigenDecomposition) {
    Matrix2cd matr;
    matr.setConstant(0.5);
    HilbertSpace space(2);
    
    QuantumState state(matr, space);
    Vector2d values(0, 1);
    Vector2cd vec1(-1, 1); vec1.normalize();
    Vector2cd vec2(1, 1); vec2.normalize();
    Matrix2cd vectors; // will contain eigen vectors vec1 and vec2 as columns
    vectors.col(0) = vec1;
    vectors.col(1) = vec2;
    
    EXPECT_EQ(true, values.isApprox(state.eigenValues()));
    EXPECT_EQ(true, vectors.isApprox(state.eigenVectors()));
}

TEST(QST, TestPureStateDetermination) {
    Matrix2cd matrPure, matrMixed;
    matrPure << 0.5, 0.5, 0.5, 0.5;
    matrMixed << 0.5, -0.25, -0.25, 0.5;
    HilbertSpace space(2);
    
    QuantumState pureState(matrPure, space), mixedState(matrMixed, space);
    
    EXPECT_EQ(true, pureState.isPure());
    EXPECT_EQ(false, mixedState.isPure());
}

TEST(QST, TestTensorProduct) {
    QuantumState state = QuantumState::tensor(QuantumState(Vector2cd(1,0), HilbertSpace(2)), QuantumState(Vector2cd(0,1), HilbertSpace(2)));
    Matrix4cd res = Matrix4cd::Zero();
    res(1,1)=1;
    
    EXPECT_EQ(res, state.densityMatrix());
    EXPECT_EQ(2, state.space().rank());
    EXPECT_EQ(2, state.space().dimension(1));
}

TEST(QST, TestPartTrace) {
    QuantumState state1(Vector2cd(1,1), HilbertSpace(2)), state2(Vector2cd(1,-1), HilbertSpace(2));
    QuantumState tens = QuantumState::tensor(state1, state2);
    
    EXPECT_EQ(state1, tens.partialTrace(1));
    EXPECT_EQ(state2, tens.partialTrace(0));
    EXPECT_ANY_THROW(tens.partialTrace(-1));
    EXPECT_ANY_THROW(tens.partialTrace(2));
}