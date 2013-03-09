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


#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "Eigen/Core"
#include "quantumstate.h"
#include <vector>
#include <map>
using namespace Eigen;

class Measurement
{
public:
    Measurement();
    Measurement(std::vector < MatrixXcd > operators, std::vector<std::string> labels);
    
    void addOperator(MatrixXcd matr, std::string label);
    
    std::map<std::string, double> probabilities(QuantumState state);
    std::string performOn(QuantumState* state);
    
    std::vector<MatrixXcd> operators();
    std::vector<std::string> labels();
    bool isValid();
    std::string error();
    
private:
    std::vector<MatrixXcd> _operators;
    std::vector<std::string> _labels;
    bool _valid;
    std::string _err;
    bool _checkOperatorsHaveTheSameSize();
    void _checkOperatorsAreValid();
    bool _checkOperatorsSumEqualToIdentity();
    bool _checkOperatorsAreHermit();
    bool _checkOperatorsArePositive();
};

#endif // MEASUREMENT_H
