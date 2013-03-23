#cmake_minimum_required(2.8)

project(quantemul)

add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_subdirectory(eigen)
#include_directories(
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(qtest models/kronecker_tensor.cpp models/measurement.cpp models/unitary_transformation.cpp models/quantum_state.cpp models/hilbert_space.cpp test_main.cpp 
	    models/transforms/toffoligate.cpp models/transforms/controlledugate.cpp models/transforms/swapgate.cpp models/transforms/phaseshiftgate.cpp models/transforms/pauligate.cpp models/transforms/hadamardgate.cpp 	    
	    models/test/test.cpp models/test/kronecker_tensor_test.cpp models/test/hilbert_space_test.cpp models/test/quantum_state_test.cpp models/test/unitary_transformation_test.cpp models/test/transformationstest.cpp models/test/measurementtest.cpp)
add_subdirectory(models/test)
target_link_libraries(qtest gtest gtest_main)

add_executable(quantemul views/index_view.cpp controllers/index_controller.cpp models/kronecker_tensor.cpp models/measurement.cpp models/unitary_transformation.cpp models/quantum_state.cpp models/hilbert_space.cpp main.cpp 
models/transforms/toffoligate.cpp models/transforms/controlledugate.cpp models/transforms/swapgate.cpp models/transforms/phaseshiftgate.cpp models/transforms/pauligate.cpp models/transforms/hadamardgate.cpp)

add_test(
    NAME qtest
    COMMAND qtest
)

#install(TARGETS quantemul RUNTIME DESTINATION bin)