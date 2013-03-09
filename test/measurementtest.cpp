#include <gtest/gtest.h>
#include "../measurement.h"
#include "../Eigen/Dense"

using namespace std;

TEST(MesurementTest, TestConstructWithSetOfOperators) {
    vector<MatrixXcd> operators;
    MatrixXcd matr(2,2); matr << 1,0,0,0;
    operators.push_back(matr);
    matr << 0,0,0,1;
    operators.push_back(matr);
    
    Measurement measure(operators);
    
    EXPECT_EQ(true, measure.isValid());
}

TEST(MeasurementTest, TestOperatorSet) {
    Measurement measure;
    MatrixXcd matr(2,2); matr << 1,0,0,0;
    measure.addOperator(matr);
    matr << 0,0,0,1;
    measure += matr;
    
    EXPECT_EQ(2, measure.operators().size());
    EXPECT_EQ(true, measure.isValid());
}

TEST(MeasurementTest, TestDifferentSizeOperators) {
    Measurement measure;
    MatrixXcd matr2(2,2), matr3(3,3);
    matr2 << 1,0,0,0; matr3 << 0,0,0,0,0,0,0,0,1;
    
    (measure += matr2) += matr3;
    
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
    measure.addOperator(matr);
    measure.addOperator(matr);
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("Operators sum must be equal to the identity operator", measure.error());
}

TEST(MeasurementTest, TestConstructWithNonHermitOperators) {
    Measurement measure;
    MatrixXcd matr(2,2);
    matr << 0.5, 0.5, std::complex<double>(0, 0.5), 0.5;
    measure.addOperator(matr);
    matr << 0.5, -0.5, std::complex<double>(0, -0.5), 0.5;
    measure.addOperator(matr);
    
    EXPECT_EQ(false, measure.isValid());
    EXPECT_EQ("Operators must be Hermit", measure.error());
}