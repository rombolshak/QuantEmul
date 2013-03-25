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
#include "../Eigen/Eigenvalues"
#include "kronecker_tensor.h"
#include <stdexcept>
#include <string>

std::string i_to_string(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();
    
    return s;
}

#ifndef Constructors

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

Measurement::Measurement(MatrixXcd observable)
{
    ComplexEigenSolver<MatrixXcd> solver(observable);
    MatrixXcd vectors = solver.eigenvectors();
    for (int i = 0; i < vectors.cols(); ++i)
	addOperator(vectors.col(i) * vectors.col(i).transpose(), i_to_string(i));    
    _checkOperatorsAreValid();
}

void Measurement::addOperator(MatrixXcd matr, std::string label)
{
    _operators.push_back(matr);
    _labels.push_back(label);
    _checkOperatorsAreValid();
}

#endif

#ifndef Checks

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

void Measurement::_checkSpacesDimensionsMatches(HilbertSpace space, int subsystem)
{
    if (_operators[0].cols() != (subsystem == -1 ? space.totalDimension() : space.dimension(subsystem)))
	throw std::invalid_argument("State space dimension does not match operators dimension");
}

#endif

#ifndef Performing

MatrixXcd Measurement::_getMeasurementMatrix(int subsystem, int num, const HilbertSpace& space)
{
    if (subsystem == -1)
	return _operators[num];
    
    return KroneckerTensor::expand(_operators[num], subsystem, space.dimensions());
}

std::map< std::string, double > Measurement::probabilities(const QuantumState& state, int subsystem)
{
    if (!_valid) 
	throw std::runtime_error("You cannot test probabilities because " + _err);
    _checkSpacesDimensionsMatches(state.space(), subsystem);
    
    std::map< std::string, double > res;
    for (int i = 0; i < _operators.size(); ++i) {
	MatrixXcd measureMatr = _getMeasurementMatrix(subsystem, i, state.space());
	res[_labels[i]] = (state.densityMatrix() * measureMatr).trace().real();
    }
    return res;
}

std::string Measurement::performOn(QuantumState* state, int subsystem)
{
    if (!_valid) 
	throw std::runtime_error("You cannot perform this measurement because " + _err);
    _checkSpacesDimensionsMatches(state->space(), subsystem);
    
    std::map< std::string, double > probs = probabilities(*state, subsystem);
    
    //srand(time(NULL));
    double r = (double) rand() / RAND_MAX;
    
    int outcomeNum = 0;
    double probSum = probs[_labels[outcomeNum]];
    
    while (r > probSum) 
	probSum += probs[_labels[++outcomeNum]];
    
    // now in outcomeNum we have our outcome index
    // lets perform changing state
    // first, we need to compute square root of operator
    
    MatrixXcd measureMatr = _getMeasurementMatrix(subsystem, outcomeNum, state->space());
    SelfAdjointEigenSolver<MatrixXcd> solver(measureMatr);
    MatrixXcd root = solver.operatorSqrt();
    
    MatrixXcd newMatrix = (root * state->densityMatrix() * root) / probs[_labels[outcomeNum]];
    state->setMatrix(newMatrix);
    
    return _labels[outcomeNum];
}

std::string Measurement::performOnSubsystem(QuantumState* state, int subsystem)
{
    return performOn(state, subsystem);
}


#endif

#ifndef Getters


Proector::Proector(HilbertSpace space)
{
    for (int i = 0; i < space.totalDimension(); ++i) {
	VectorXi toLabel = space.getVector(i);
	VectorXcd op = space.getBasisVector(toLabel);
	addOperator(op * op.transpose(), _vecToLabel(toLabel));
    }
}

std::string Proector::_vecToLabel(VectorXi vec)
{
    std::string v = "";
    for (int i = 0; i < vec.size(); ++i) {
	if (i != 0) v += ",";
	v += i_to_string(vec[i]);
    }
    return "|" + v + "><" + v + "|";
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

#endif