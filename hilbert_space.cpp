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


#include "hilbert_space.h"
#include <stdexcept>

using namespace std;

#ifndef Constructors

HilbertSpace::HilbertSpace()
{
    _rank = 0;
    _dim = 0;
}

HilbertSpace::HilbertSpace(uint dim)
{
    if (dim == 0) throw invalid_argument("Dimension cannot be zero");
    _rank = 1;
    _dimensions.push_back(dim);
    _dim = dim;
}

HilbertSpace::HilbertSpace(const std::vector< uint >& dimensions) 
{
    _rank = dimensions.size();
    _dim = 1; // need to prevent multiply with default value
    for (int i = 0; i < _rank; ++i)
	if (dimensions[i] == 0)
	    throw invalid_argument("Dimension cannot be zero");
	else _dim *= dimensions[i];
    _dimensions = dimensions;
}

#endif

#ifndef Tensor
HilbertSpace HilbertSpace::tensor(const HilbertSpace& first, const HilbertSpace& second)
{
    HilbertSpace space = first;
    space.tensorWith(second);
    return space; // молимся, чтоб память выделялась не на стеке...
}

void HilbertSpace::tensorWith(const HilbertSpace& second)
{
    _rank += second._rank;
    for (int i = 0; i < second._rank; ++i)
	_dimensions.push_back(second._dimensions[i]);
    _dim *= second._dim;
}

#endif

#ifndef Ket_bra

VectorXi HilbertSpace::getVector(int index) const
{
    if (index < 0 || index >= _dim)
	throw std::invalid_argument("Index must be between 0 and space dimension");
    VectorXi vec(_rank);
    for (int i = _rank - 1; i >= 0; --i) {
	vec[i] = index % _dimensions[i];
	index = (int) floor(1.0 * index / _dimensions[i]);
    }
    return vec;
}

VectorXi HilbertSpace::getVector(HilbertSpace space, int index)
{
    return space.getVector(index);
}

int HilbertSpace::getIndex(VectorXi vec) const
{
    if (vec.size() != _rank)
	throw std::invalid_argument("Vector size must be equal to space dimension");
    int index = vec[vec.size() - 1];
    int multiplier = _dimensions[_rank - 1];
    for (int i = vec.size() - 2; i >= 0; --i) {
	index += vec[i] * multiplier;
	multiplier *= _dimensions[i];
    }
	
    return index;
}

int HilbertSpace::getIndex(HilbertSpace space, VectorXi vec)
{
    return space.getIndex(vec);
}

VectorXcd HilbertSpace::getBasisVector(VectorXi basisVec) const
{
    if (basisVec.size() != _rank)
	throw std::invalid_argument("Basis vector size must be equal to space dimension");
    
    VectorXcd vec(_dim);
    vec.setZero();
    vec[getIndex(basisVec)] = 1;
    
    return vec;
}

#endif

bool HilbertSpace::operator==(const HilbertSpace& other) const
{
    return _dimensions == other._dimensions;
}

bool HilbertSpace::operator!=(const HilbertSpace& other) const
{
    return !operator==(other);
}

#ifndef Getters

int HilbertSpace::rank() const 
{
    return _rank;
}

int HilbertSpace::dimension(int index) const
{
    if (index < 0) throw out_of_range("Did you ever seen an negative dimension index? You should stop take drugs, really");
    if (index >= _rank) throw out_of_range("This space is less than you think. There is no dimension with such big index, sorry");
    return _dimensions[index];
}

vector<uint> HilbertSpace::dimensions() const
{
    return _dimensions;
}


int HilbertSpace::totalDimension() const
{
    return _dim;
}

#endif
