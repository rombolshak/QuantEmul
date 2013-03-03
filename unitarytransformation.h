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

#include "Eigen/Dense"
#include "hilbertspace.h"
#include "quantumstate.h"

using namespace Eigen;

class UnitaryTransformation
{
public:
    UnitaryTransformation(MatrixXcd oldBasis, MatrixXcd newBasis, HilbertSpace space);
    UnitaryTransformation(MatrixXcd matrix, HilbertSpace space);
    
    MatrixXcd transformMatrix();
    HilbertSpace space();
    QuantumState* applyTo(QuantumState* state);
    
protected:
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
