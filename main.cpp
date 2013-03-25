/*
 *  Copyright (c) 2013 Роман Большаков <rombolshak@russia.ru>
 * 
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 * 
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */
#include "main_helper.h"
#include "models/quantum_state.h"


int main(int argc, char **argv) {
    srand(time(0));
    MainHelper().run();// h;
//     h.printWelcome();
//     
//     int n = h.askDimension();
//     QuantumState state = h.createInitialState(n);
//     
//     cout << "Initial state:" << endl << state.densityMatrix() << endl;
//     
//     int choice = h.askChoice();
//     h.prepareState(&state, choice);
//     
//     cout << "State:" << endl << state.densityMatrix() << endl;
//     
//     vector<int> subsystems = h.askSubsystems();
//     vector<string> results = h.performMeasurementsOn(&state, subsystems);
//     
//     for (int i = 0; i < results.size(); ++i)
// 	cout << "Measurement result of subsystem #" << subsystems[i] << " is " << results[i] << endl;
//     
    return 0;
}

