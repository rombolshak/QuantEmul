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


#ifndef CONTROLLEDUGATE_H
#define CONTROLLEDUGATE_H

#include "../unitary_transformation.h"

/**
 * Class representing Controlled U gate. This is 2 qubit transform. When the first is equal to 1, apply transform U to the second
 */
class ControlledUGate : public UnitaryTransformation
{
public:
    /**
     * Construct controlled transform
     * @param transform 1-cubit transformation. Be sure to provide unitary matrix
     */
    ControlledUGate(Matrix2cd transform) {init(transform);}
protected:
    ControlledUGate(){}
    void init(Matrix2cd transform);
};

/**
 * Class representing the CNOT gate: apply NOT the the second qubit if the first equal to 1
 */
class CNOTGate : public ControlledUGate
{
public:
    CNOTGate() {
	Matrix2cd matr; matr << 0,1,1,0;
	init(matr);
    }
};

#endif // CONTROLLEDUGATE_H
