#cmake_minimum_required(2.8)

project(quantemul)

add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_subdirectory(eigen)
#include_directories(
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(quantemul main.cpp)
target_link_libraries(quantemul gtest gtest_main)

add_test(
    NAME quantemul
    COMMAND quantemul
)

install(TARGETS quantemul RUNTIME DESTINATION bin)
