#include <gtest/gtest.h>
#include "../measurement.h"
#include "../Eigen/Dense"
#include "../quantum_state.h"

using namespace std;

TEST(MeasurementTest, TestConstructWithSetOfOperators) {
    vector<MatrixXcd> operators;
    vector<string> labels;
    MatrixXcd matr(2,2); 
    
    matr << 1,0,0,0;
    operators.push_back(matr);
    labels.push_back("1");
    
    matr << 0,0,0,1;
    operators.push_back(matr);
    labels.push_back("2");
    
    Measurement measure(operators, labels);
    
    EXPECT_EQ(true, measure.isValid());
}

TEST(MeasurementTest, TestOperatorSet) {
    Measurement measure;
    MatrixXcd matr(2,2); matr << 1,0,0,0;
    measure.addOperator(matr, "0");
    matr << 0,0,0,1;
    measure.addOperator(matr, "1");
    
    EXPECT_EQ(2, measure.operators().size());
    EXPECT_EQ(true, measure.isValid());
}

TEST(MeasurementTest, TestDifferentSizeOperators) {
    Measurement measure;
    MatrixXcd matr2(2,2), matr3(3,3);
    matr2 << 1,0,0,0; matr3 << 0,0,0,0,0,0,0,0,1;
    
    measure.addOperator(matr2, "2");
    measure.addOperator(matr3, "3");
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("All operators in one set must be the same size", measure.error());
}

TEST(MeasurementTest, TestConstructWithEmptySet) {
    Measurement measure;
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("Operators set cannot be empty", measure.error());
}

TEST(MeasurementTest, TestConstructWithOperatorsWhichSumIsNotUdentity) {
    Measurement measure;
    MatrixXcd matr(2,2);
    matr << 1,0,0,0;
    measure.addOperator(matr, "1");
    measure.addOperator(matr, "2");
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("Operators sum must be equal to the identity operator", measure.error());
}

TEST(MeasurementTest, TestConstructWithNonHermitOperators) {
    Measurement measure;
    MatrixXcd matr(2,2);
    matr << 0.5, 0.5, std::complex<double>(0, 0.5), 0.5;
    measure.addOperator(matr, "1");
    matr << 0.5, -0.5, std::complex<double>(0, -0.5), 0.5;
    measure.addOperator(matr, "2");
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("Operators must be Hermit", measure.error());
}

TEST(MeasurementTest, TestProbabilities) {
    Measurement measure;
    Matrix2cd op; 
    op << 1,0,0,0;    measure.addOperator(op, "|0><0|");
    op << 0,0,0,1;    measure.addOperator(op, "|1><1|");
    
    QuantumState state(Vector2cd(1,1), HilbertSpace(2));    
    EXPECT_EQ(true, abs(0.5 - measure.probabilities(state)["|0><0|"]) < 1.0e-15);
    EXPECT_EQ(true, abs(0.5 - measure.probabilities(state)["|1><1|"]) < 1.0e-15);
    
    state = QuantumState(Vector2cd(1,0), HilbertSpace(2));
    EXPECT_EQ(true, abs(1 - measure.probabilities(state)["|0><0|"]) < 1.0e-15);
    EXPECT_EQ(true, abs(0 - measure.probabilities(state)["|1><1|"]) < 1.0e-15);
}

TEST(MeasurementTest, TestPerformingMeasure) {
    Measurement measure;
    Matrix2cd pr0, pr1; 
    pr0 << 1,0,0,0;    measure.addOperator(pr0, "|0><0|");
    pr1 << 0,0,0,1;    measure.addOperator(pr1, "|1><1|");
    
    QuantumState state(Vector2cd(1,1), HilbertSpace(2));
    
    if (measure.performOn(&state) == "|0><0|")
    {
	EXPECT_EQ(pr0, state.densityMatrix());
	EXPECT_EQ("|0><0|", measure.performOn(&state));
    }
    else
    {
	EXPECT_EQ(pr1, state.densityMatrix());
	EXPECT_EQ("|1><1|", measure.performOn(&state));
    }
}

TEST(MeasurementTest, TestConstructWithObservable) {
    MatrixXcd ob(2,2);
    ob << 0,1,1,0; // Pauli-X
    
    Measurement measure(ob);
    QuantumState state(Vector2cd(1,1), HilbertSpace(2));
    
    EXPECT_EQ(true, measure.isValid());
    EXPECT_EQ(0, measure.probabilities(state)["1"]);
    EXPECT_EQ("0", measure.performOn(&state));
}