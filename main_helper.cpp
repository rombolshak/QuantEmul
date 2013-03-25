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


#include "main_helper.h"
#include "models/kronecker_tensor.h"
#include "models/transforms/hadamardgate.h"
#include "models/transforms/controlledugate.h"
#include "models/measurement.h"

MainHelper::MainHelper()
{

}

void MainHelper::run()
{
    printWelcome();
    state = createInitialState(askDimension());
    prepareState(askChoice());
    vector<int> subsystems = askSubsystems();
    vector<string> results = performMeasurementsOn(subsystems);
    
    for (int i = 0; i < results.size(); ++i)
    cout << "Measurement result of subsystem #" << subsystems[i] << " is " << results[i] << endl;
}

int MainHelper::askDimension() {
    cout << "I'm going to prepare initial state. I need the rank of state space." << endl;
    int n;
    do {
	cout << "Please give me an integer above or equal 1" << endl << "> ";    
	cin >> n;
    }
    while (n < 1);
    return n;
}

void MainHelper::printWelcome() {
    cout << "Welcome to QuantEmul" << endl << endl;
}

QuantumState* MainHelper::createInitialState(int n)
{
    int size = (int)pow(2, n);
    MatrixXcd matr(size, size);
    matr(0,0) = 1;
    vector<uint> dims;
    for (int i = 0; i < n; ++i)
	dims.push_back(2);
    return new QuantumState(matr, HilbertSpace(dims));
}

int MainHelper::askChoice()
{
    cout << "What kind of state do you want?" << endl <<
    "1) 1/sqrt(2) * (|0>¤n + |1>¤n)" << endl <<
    "2) (1/sqrt(2) * (|0> + |1>)) ¤n" << endl;
    int c;
    do {
	cout << "1 or 2?" << endl << "> ";
	cin >> c;
    }
    while ((c < 1) || (c > 2));
    return c;
}

void MainHelper::prepareState(int choice)
{
    int n = state->space().rank();    
    MatrixXcd op = KroneckerTensor::getIdentityMatrix((int)pow(2, n));
    
    if (choice == 1) {
	HilbertSpace space = state->space();
	std::vector<uint> dims = space.dimensions();
	dims.erase(dims.begin()); // use feature of expand() that does not control dimension of the i-th item in dimensions
	MatrixXcd cnot = CNOTGate().transformMatrix();
	for (int i = n - 2; i >= 0; --i) {
	    op *= KroneckerTensor::expand(cnot, i, dims);
// 	    cout << "op: " << endl << op << endl;
	}
	op *= HadamardGate(0, space).transformMatrix();
// 	cout << "op: " << endl << op << endl;
    }
    else if (choice == 2)	
	for (int i = 0; i < n; ++i)
	    op *= HadamardGate(i, state->space()).transformMatrix();	
    
    UnitaryTransformation tr(op, state->space());
    tr.applyTo(state);
}

std::vector< int > MainHelper::askSubsystems()
{
    cout << "Now lets MEASURE!" << endl <<
    "Provide me indicies of subsystems you want to measure" << endl <<
    "End sequense with -1 to let me know this is the end of it all" << endl << "> ";
    vector<int> res;
    int s;
    do {
	cin >> s;
	if (s != -1)
	    res.push_back(s);
    } while (s != -1);
    return res;
}

vector< string > MainHelper::performMeasurementsOn(const std::vector< int >& subsystems)
{
    vector<string> res;
    Measurement measure = Proector(HilbertSpace(2));
    for (int i = 0; i < subsystems.size(); ++i) {
// 	cout << "Probabilities on measure #" << i << ": ";
	map<string, double> probs = measure.probabilities(*state, subsystems[i]);
// 	for (auto& kv : probs) {
// 	    std::cout << kv.first << " has value " << kv.second << std::endl;
// 	}
	res.push_back(measure.performOnSubsystem(state, subsystems[i]));
// 	cout << "After measure #" << i << " state:" << endl << state->densityMatrix() << endl;
    }
    return res;
}
