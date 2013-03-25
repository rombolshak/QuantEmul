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


#include "kronecker_tensor.h"

MatrixXcd KroneckerTensor::product(const MatrixXcd& a, const MatrixXcd& b)
{
    MatrixXcd res(a.rows() * b.rows(), a.cols() * b.cols());
    
    for (int i = 0; i < a.rows(); ++i)
	for (int j = 0; j < a.cols(); ++j)
	    for (int k = 0; k < b.rows(); ++k)
		for (int l = 0; l < b.cols(); ++l)
		    res(i * b.rows() + k, j * b.cols() + l) = a(i, j) * b(k, l);
    return res;
}

MatrixXcd KroneckerTensor::expand(const MatrixXcd& initial, int index, const std::vector< uint >& dimensions)
{
    MatrixXcd res(1,1);
    res(0,0) = 1;
    for (int i = 0; i < dimensions.size(); ++i)
	if (i == index)
	    res = KroneckerTensor::product(res, initial);
	else res = KroneckerTensor::product(res, getIdentityMatrix(dimensions[i]));
    return res;
}

MatrixXcd KroneckerTensor::getIdentityMatrix(uint dimension)
{
    MatrixXcd i(dimension, dimension);
    i.setIdentity();
    return i;
}