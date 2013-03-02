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


#include "unitarytransformation.h"
#include "Eigen/LU"
#include <stdexcept>

UnitaryTransformation::UnitaryTransformation(MatrixXcd oldBasis, MatrixXcd newBasis)
{
    _checkMatricesAreSquare(oldBasis, newBasis);
    _checkMatricesHaveTheSameSize(oldBasis, newBasis);
    
    for (int i = 0; i < oldBasis.cols(); ++i) {
	oldBasis.col(i).normalize();
	newBasis.col(i).normalize();
    }
    _matrix = oldBasis.inverse() * newBasis;
}

void UnitaryTransformation::_checkMatricesAreSquare(MatrixXcd oldBasis, MatrixXcd newBasis)
{
    if (oldBasis.cols() != oldBasis.rows())
	throw std::invalid_argument("Matrix of old basis must be square");
    if (newBasis.cols() != newBasis.rows())
	throw std::invalid_argument("Matrix of new basis must be square");
}

void UnitaryTransformation::_checkMatricesHaveTheSameSize(MatrixXcd oldBasis, MatrixXcd newBasis)
{
    if (oldBasis.cols() != newBasis.cols())
	throw std::invalid_argument("Matrices of basises must be the same size. How do you imagine transform from space dimension 6 to space dimension 42, for example?");
}

MatrixXcd UnitaryTransformation::transformMatrix()
{
    return _matrix;
}
