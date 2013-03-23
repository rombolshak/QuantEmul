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


#ifndef UNITARYTRANSFORMATION_H
#define UNITARYTRANSFORMATION_H

#include "../Eigen/Dense"
#include "hilbert_space.h"
#include "quantum_state.h"

using namespace Eigen;

/**
 * General class for unirary transformations
 */
class UnitaryTransformation
{
public:
    /**
     * Construct new transform by the pair of basises
     * @param oldBasis Basis in the current state
     * @param newBasis Basis after transform
     * @param space Hilbert space in which transform can be applied
     */
    UnitaryTransformation(MatrixXcd oldBasis, MatrixXcd newBasis, HilbertSpace space);
    
    /**
     * Construct new transform by the unirary matrix
     * @param matrix Unitary matrix of transform
     * @param space Hilbert space in which transform can be applied
     */
    UnitaryTransformation(MatrixXcd matrix, HilbertSpace space);
    
    /**
     * Returns unirary matrix of the transform
     */
    MatrixXcd transformMatrix();
    
    /**
     * Returns space in which transform can be applied
     */
    HilbertSpace space();
    
    /**
     * Apply current transform to the specified state. State will be changed according to transform matrix
     * Returns the same state in order to do the chain transform ABCs: A.applyTo(B.applyTo(C.applyTo(s)));
     */
    QuantumState* applyTo(QuantumState* state);
    
protected:
    /**
     * Empty constructor. Assume to be called only in derived class and derived class MUST set _matrix and _space variables
     */
    UnitaryTransformation();
    MatrixXcd _matrix;
    HilbertSpace _space;
private:
    void _checkMatricesAreSquare(MatrixXcd oldBasis, MatrixXcd newBasis);
    void _checkMatricesHaveTheSameSize(MatrixXcd oldBasis, MatrixXcd newBasis);
    void _checkMatrixIsSquare(MatrixXcd matr);
    void _checkMatrixIsUnitary(MatrixXcd matrix);
    void _continueConstruct();
    void _checkSpace();
};

#endif // UNITARYTRANSFORMATION_H
