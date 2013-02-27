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


#include "quantumstate.h"
#include <stdexcept>

QuantumState::QuantumState(MatrixXcd matr)
{
    if (matr.cols() == 1) // state represented by vector, need to construct matrix	
	_density = matr * matr.transpose();
    else {
	CheckMatrixIsSquare(matr);
	CheckMatrixIsDensityMatrix(matr);
	_density = matr;
    }
}

void QuantumState::CheckMatrixIsSquare(MatrixXcd matr)
{
    if (matr.cols() != matr.rows())
	throw std::invalid_argument("Matrix should be square, and your matrix is not. Be careful");
}

void QuantumState::CheckMatrixIsDensityMatrix(MatrixXcd matr)
{
    if (matr != matr.adjoint())
	throw std::invalid_argument("Matrix should be hermit");
}

MatrixXcd QuantumState::densityMatrix()
{
    return _density;
}

