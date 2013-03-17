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
#include "quantum_state.h"
#include <vector>
#include <map>
using namespace Eigen;

/**
 * Class representing general measurement of quantum state
 */
class Measurement
{
public:
    
    /**
     * Constructs an empty measurement. You will need to add operators via addOperator()
     */
    Measurement();
    
    /**
     * Constructs measurement with ready set of operators that are Hermit, positive-defined and their sum equal to identity operator
     * @param operators Set of operators that are Hermit, positive-defined and their sum equal to identity operator
     * @param labels Set of outcome labels corresponding to each operator
     */
    Measurement(std::vector < MatrixXcd > operators, std::vector<std::string> labels);
    
    /**
     * Constructs measurement via observable. Set of operators will be constructed automatically as well as labels. Labels will look like "0", "1" and so on
     * @param observable Observable operator to construct measurement
     */
    Measurement(MatrixXcd observable);
    
    /**
     * Add one more operator to the existing set
     * @param matr Operator matrix. Should be Hermit and positive-defined
     * @param label Label of outcome that corresponds to this operator
     */
    void addOperator(MatrixXcd matr, std::string label);
    
    /**
     * Show if everything is OK during construct. You should check it before testing probabilities() or perfoming measurement
     * If smth wrong, the error may be retrieved through error().
     * 
     * Possible problems why it is not valid:
     * 1. Operators are not square
     * 2. Operators have different sizes (e.g. one is 2x2 and second is 3x3)
     * 3. Operators are not Hermit
     * 4. Operators are not positive-defined
     * 5. Operators' sum not equal to identity
     */
    bool isValid();
    
    /**
     * Contains last error happened during construction
     */
    std::string error();
    
    /**
     * Returns probabilities of each outcome possible in this measurement if it was applied to the specified state
     * @param state Quantum state which space matches operators dimension
     * @return Map where keys are outcome labels and values are probabilities of this outcomes, from 0 to 1, inclusive
     */
    std::map<std::string, double> probabilities(QuantumState state);
    
    /**
     * Perform this measurement on the specified state
     * @param state Quantum state to perform measurement on. Be sure about space matching
     * @return Label of outcome which occured. Notice that state has changed
     */
    std::string performOn(QuantumState* state);

    /**
     * Full operator set of this measurement
     */
    std::vector<MatrixXcd> operators();
    
    /**
     * Full labels set corresponding to the operators()
     */
    std::vector<std::string> labels();
    
private:
    std::vector<MatrixXcd> _operators;
    std::vector<std::string> _labels;
    bool _valid;
    std::string _err;
        
    void _checkOperatorsAreValid();
    bool _checkOperatorsHaveTheSameSize();
    bool _checkOperatorsSumEqualToIdentity();
    bool _checkOperatorsAreHermit();
    bool _checkOperatorsArePositive();
    void _checkSpacesDimensionsMatches(HilbertSpace space);
};

#endif // MEASUREMENT_H
