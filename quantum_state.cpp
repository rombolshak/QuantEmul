/*
    Copyright (c) 2013 Роман Большаков <rombolshak@russia.ru>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#include "quantum_state.h"
#include "kronecker_tensor.h"
#include <stdexcept>

QuantumState::QuantumState(MatrixXcd matr, const HilbertSpace & space)
{
    if (matr.cols() == 1) {// state represented by vector, need to construct matrix	
	matr.normalize();
	_density = matr * matr.transpose();
    }
    else {
	_checkMatrixIsSquare(matr);
	_density = matr;
    }
    
    _calculateEigenValuesAndVectors(_density);
    _checkMatrixIsDensityMatrix(_density);
    _checkSpaceDimension(_density, space);
    _space = space;
}

#include <iostream>
QuantumState QuantumState::tensor(const QuantumState& first, const QuantumState& second)
{
    QuantumState res (
	KroneckerTensor::product(first._density, second._density), HilbertSpace::tensor(first._space, second._space));//*tensorSpace);

    return res;
}


#ifndef Checks

void QuantumState::_calculateEigenValuesAndVectors(MatrixXcd matr) {
    if (!_checkMatrixIsSelfAdjoined(matr))
	throw std::invalid_argument("Matrix should be selfadjoined");
    
    SelfAdjointEigenSolver<MatrixXcd> solver(matr);
    if (solver.info() != Eigen::Success)
	throw std::runtime_error("Something is wrong with eigen solver");
    
    _eigenValues = solver.eigenvalues();
    _eigenVectors = solver.eigenvectors();
}

void QuantumState::_checkMatrixIsSquare(MatrixXcd matr) {
    if (matr.cols() != matr.rows())
	throw std::invalid_argument("Matrix should be square, and your matrix is not. Be careful");
}

bool QuantumState::_checkMatrixIsSelfAdjoined(MatrixXcd matr) {
    return (matr.isApprox(matr.adjoint()));
}

void QuantumState::_checkMatrixIsDensityMatrix(MatrixXcd matr) {
    for (int i = 0; i < _eigenValues.rows(); ++i)
	if (abs(_eigenValues[i]) > 1.0e-15) // if far from zero
	    if (_eigenValues[i] < 0) // we dont like negative values
		throw std::invalid_argument("This is not density matrix because it contains negative eigen values: ");
    
    if (abs(matr.trace() - std::complex< double >(1, 0)) > 1.0e-15)
	throw std::invalid_argument("Matrix should have trace equal to 1");
}

void QuantumState::_checkSpaceDimension(MatrixXcd matr, HilbertSpace space) {
    if (space.totalDimension() != matr.rows())
	throw std::invalid_argument("Space total dimension shold be the same as matrix is");
}

#endif

bool QuantumState::isPure() {
    MatrixXcd square = _density * _density;
    return abs(square.trace() - std::complex< double >(1, 0)) < 1.0e-15;
}

void QuantumState::setMatrix(MatrixXcd matr) {
    _checkMatrixIsSquare(matr);
    _checkSpaceDimension(matr, _space);
    _calculateEigenValuesAndVectors(matr);
    _checkMatrixIsDensityMatrix(matr);
    _density = matr;
}

#ifndef Getters

HilbertSpace QuantumState::space() {
    return _space;
}

MatrixXcd QuantumState::densityMatrix() {
    return _density;
}

VectorXd QuantumState::eigenValues() {
    return _eigenValues;
}

MatrixXcd QuantumState::eigenVectors() {
    return _eigenVectors;
}

#endif