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


#include "measurement.h"
#include "Eigen/Eigenvalues"
#include <stdexcept>

Measurement::Measurement()
{
    _err = "Operators set cannot be empty";
    _valid = false;
}

Measurement::Measurement(std::vector<MatrixXcd> operators, std::vector<std::string> labels)
{
    if (operators.size() != labels.size())
	throw std::invalid_argument("Number of labels must be the same as operators");
    _operators = operators;
    _labels = labels;
    _checkOperatorsAreValid();
}

void Measurement::addOperator(MatrixXcd matr, std::string label)
{
    _operators.push_back(matr);
    _labels.push_back(label);
    _checkOperatorsAreValid();
}

#include <iostream>
void Measurement::_checkOperatorsAreValid()
{
    if (true 
	&& _checkOperatorsHaveTheSameSize()
	&& _checkOperatorsSumEqualToIdentity()
	&& _checkOperatorsAreHermit()
	&& _checkOperatorsArePositive()
    )
	_valid = true;
	
	else _valid = false;
}

bool Measurement::_checkOperatorsHaveTheSameSize()
{
    if (_operators.empty()) return true;
    int size = _operators[0].cols();
    for (int i = 0; i < _operators.size(); ++i) {
	if (_operators[i].cols() != _operators[i].rows()) 	{_err = "Operators must be square"; return false;}
	if (_operators[i].cols() != size)			{_err = "All operators in one set must be the same size"; return false;}
    }
    return true;
}

bool Measurement::_checkOperatorsSumEqualToIdentity()
{
    MatrixXcd  identity(_operators[0].cols(), _operators[0].cols());
    identity.setIdentity();
    
    MatrixXcd res(_operators[0].cols(), _operators[0].cols());
    res.setZero();
    
    for (int i = 0; i < _operators.size(); ++i)
	res += _operators[i];
    
    if (!res.isApprox(identity)) {
	_err = "Operators sum must be equal to the identity operator";
	return false;
    }
    return true;
}

bool Measurement::_checkOperatorsAreHermit()
{
    for (int i = 0; i < _operators.size(); ++i)
	if (_operators[i] != _operators[i].adjoint()) {
	    _err = "Operators must be Hermit";
	    return false;
	}
    return true;
}

bool Measurement::_checkOperatorsArePositive()
{
    for (int i = 0; i < _operators.size(); ++i) {	
	SelfAdjointEigenSolver<MatrixXcd> solver(_operators[i]);
	VectorXd values = solver.eigenvalues();
	for (int j = 0; j < values.size(); ++j)
	    if (values[j] < -1.0e-15) {
		_err = "Operators must have non-negative eigen values";
		return false;
	    }
    }
    return true;
}


bool Measurement::isValid()
{
    return _valid;
}

std::vector< MatrixXcd > Measurement::operators()
{
    return _operators;
}

std::string Measurement::error()
{
    return _err;
}

std::vector< std::string > Measurement::labels()
{
    return _labels;
}
