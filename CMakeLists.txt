#cmake_minimum_required(2.8)

project(quantemul)

add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_subdirectory(eigen)
#include_directories(
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(quantemul kronecker_tensor.cpp measurement.cpp unitary_transformation.cpp quantum_state.cpp hilbert_space.cpp main.cpp 
	    transforms/toffoligate.cpp transforms/controlledugate.cpp transforms/swapgate.cpp transforms/phaseshiftgate.cpp transforms/pauligate.cpp transforms/hadamardgate.cpp 	    
	    test/test.cpp test/kronecker_tensor_test.cpp test/hilbert_space_test.cpp test/quantum_state_test.cpp test/unitary_transformation_test.cpp test/transformationstest.cpp test/measurementtest.cpp)
add_subdirectory(test)
target_link_libraries(quantemul gtest gtest_main)

add_test(
    NAME quantemul
    COMMAND quantemul
)

install(TARGETS quantemul RUNTIME DESTINATION bin)

add_subdirectory(transforms)