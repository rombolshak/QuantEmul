QuantEmul
=========

Simple emulation of some quantum computer basics

Structure
=========
In models/
- hilbertspace.{h,cpp}. Represent minimum needed implementation of hilbert space
- quantumstate.{h,cpp}. Represent, as you can guess, quantum state implementation. It is not ideal, I know
- unitarytransformation.{h,cpp}. General class and methods for state transforms
- transforms/ contain several implementation of simple transforms such as NOT, CNOT, Pauli, Toffoli, SWAP
- measurement.{h.cpp}. Represent general measurements of quantum states

Compile
=======
You'll need CMake to compile this project properly

1. cd QuantEmul/directory/path
2. mkdir build
3. cd build
4. cmake ..
5. make
6. ./quantemul
Or if you wanna to run test:
7. ./qtest
If everything is OK, and there are no compilation errors, you should see all tests to be passed. Congrats! :)
