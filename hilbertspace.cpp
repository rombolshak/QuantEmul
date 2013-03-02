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


#include "hilbertspace.h"
#include <stdexcept>

using namespace std;

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


HilbertSpace::HilbertSpace(std::vector< uint > dimensions) 
{
    _rank = dimensions.size();
    _dim = 1; // need to prevent multiply with default value
    for (int i = 0; i < _rank; ++i)
	if (dimensions[i] == 0)
	    throw invalid_argument("Dimension cannot be zero");
	else _dim *= dimensions[i];
    _dimensions = dimensions;
}


int HilbertSpace::rank() 
{
    return _rank;
}

int HilbertSpace::dimension(int index)
{
    if (index < 0) throw out_of_range("Did you ever seen an negative dimension index? You should stop take drugs, really");
    if (index >= _rank) throw out_of_range("This space is less than you think. There is no dimension with such big index, sorry");
    return _dimensions[index];
}

int HilbertSpace::totalDimension()
{
    return _dim;
}


void HilbertSpace::tensorWith(const HilbertSpace& second)
{
    _rank += second._rank;
    for (int i = 0; i < second._rank; ++i)
	_dimensions.push_back(second._dimensions[i]);
    _dim *= second.totalDimension();
}



