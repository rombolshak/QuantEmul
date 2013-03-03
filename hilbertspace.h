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


#ifndef HILBERTSPACE_H
#define HILBERTSPACE_H

#include <vector>
#include <sys/types.h>

/**
 * Class representing an instance of Hilbert space or tensor product of several spaces
 */
class HilbertSpace
{
public:
    
    /**
     * Construct an empty Hilbert space that can not be used in any operations
     */
    HilbertSpace();
    
    /**
     * Construct a single Hilbert space with specified dimension
     * @param dim Dimension of Hilbert space, must be strongly positive
     */
    HilbertSpace(uint dim);
    
    /**
     * Construct a tensor product of Hilbert spaces with specified dimensions
     * @param dimensions Dimensions of components of the result space, must be strongly positive
     */
    HilbertSpace(std::vector<uint> dimensions);
    
    /**
     * Rank of the space
     */
    int rank();
    
    /**
     * Returns dimension of the subspace defined by index
     * @param index Index of needed subspace, starts from 0
     */
    int dimension(int index);
    
    /**
     * Returns sum of all subspace dimensions
     */
    int totalDimension();
    
    /**
     * Do a tensor product with specified space
     * @param second Hilbert space that will be added to current space
     */
    void tensorWith(HilbertSpace second);
    
    bool operator==(const HilbertSpace& other);
    bool operator!=(const HilbertSpace& other);

private:
    int _rank, _dim;
    std::vector< uint > _dimensions;

};

#endif // HILBERTSPACE_H
