#include <gtest/gtest.h>
#include "../transforms/hadamardgate.h"
#include "../transforms/pauligate.h"
#include "../transforms/phaseshiftgate.h"
#include "../transforms/swapgate.h"
#include "../transforms/controlledugate.h"
#include "../transforms/toffoligate.h"

TEST(TransformsTest, TestHadamardGate) {
    Vector2cd vec(1, 0);
    QuantumState state(vec, HilbertSpace(2));
    HadamardGate gate;
    Matrix2cd res; res.setConstant(0.5);
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}

TEST(TransformsTest, TestNOT) {
    Vector2cd vec(1, 0);
    QuantumState state(vec, HilbertSpace(2));
    //NOTGate gate;
    PauliGate gate(PauliGate::X);
    Matrix2cd res; res.setConstant(0); res(1,1)=1;
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}

TEST(TransformsTest, TestPhaseShift) {
    Vector2cd vec(1, 1);
    QuantumState state(vec, HilbertSpace(2));
    PhaseShiftGate gate(asin(1)*2);
    Matrix2cd res; res << 0.5, -0.5, -0.5, 0.5;
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}

TEST(TransformsTest, TestSwap) {
    Vector4cd vec(1, 1, 0, 0); // |00> + |01>
    std::vector<uint> dims; dims.push_back(2); dims.push_back(2);
    QuantumState state(vec, HilbertSpace(dims));
    SwapGate gate;
    Matrix4cd res; res.setConstant(0);
    res(0,0)=res(0,2)=res(2,0)=res(2,2) = 0.5; // |00> + |10>
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}

TEST(TransformsTest, TestCNOT) {
    Vector4cd vec(1, 0, 0, 1); // |00> + |11>
    std::vector<uint> dims; dims.push_back(2); dims.push_back(2);
    QuantumState state(vec, HilbertSpace(dims));
    CNOTGate gate;
    Matrix4cd res; res.setConstant(0);
    res(0,0)=res(0,2)=res(2,0)=res(2,2) = 0.5; // |00> + |10>
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}

TEST(TransformsTest, TestToffoli) {
    Matrix<std::complex< double >, 8, 1> vec;
    vec << 1,0,0,0,0,0,0,1; // |000> + |111>
    std::vector<uint> dims; for (int i = 0; i < 3; ++i) dims.push_back(2);;
    QuantumState state(vec, HilbertSpace(dims));
    ToffoliGate gate;
    Matrix<std::complex< double >, 8, 8> res; res.setConstant(0);
    res(0,0)=res(6,0)=res(0,6)=res(6,6)=0.5; // |000> + |110>
    
    gate.applyTo(&state);
    
    EXPECT_EQ(true, state.densityMatrix().isApprox(res));
}