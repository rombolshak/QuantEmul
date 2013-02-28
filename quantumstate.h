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


#ifndef QUANTUMSTATE_H
#define QUANTUMSTATE_H
#include "Eigen/Dense"
#include "hilbertspace.h"

using namespace Eigen;

/**
 * Class representing quantum state that can be described with density matrix and space
 */
class QuantumState
{
public:
    /**
     * Constructs an instance of quantum state
     * @param matr Density matrix of the state OR state vector (can be denormalized). Density matrix is self-adjoint (or Hermitian), positive semi-definite, of trace one
     * @param space Hilbert space in which state exists
     */
    QuantumState(MatrixXcd matr, HilbertSpace space);
    
    /**
     * Returns density matrix of current state
     */
    MatrixXcd densityMatrix();
    
    /**
     * Returns eigen values in vector of *real* numbers. Size of vector equals to the density matrix size
     */
    VectorXd eigenValues();
    
    /**
     * Returns matrix with eigen vectors as columns
     */
    MatrixXcd eigenVectors();
    
    /**
     * Show whether current state is pure or mixed
     */
    bool isPure();
    
private:
    MatrixXcd _density;
    HilbertSpace _space;
    VectorXd _eigenValues;
    MatrixXcd _eigenVectors;
    
    void CheckMatrixIsSquare(MatrixXcd matr);
    bool CheckMatrixIsSelfAdjoined(MatrixXcd matr);
    void CheckSpaceDimension(MatrixXcd matr, HilbertSpace space);
    void CalculateEigenValuesAndVectors(MatrixXcd matr);
    void CheckMatrixIsDensityMatrix(MatrixXcd matr);
};

#endif // QUANTUMSTATE_H
