cmake_minimum_required(VERSION 3.10)
project(LabMatrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(matrix src/Matrix/Matrix.cpp src/Matrix/Matrix.hpp src/main.cpp
        src/Operators/Operator.h
        src/Operators/Add/Add.cpp
        src/Operators/Add/Add.h
        src/Operators/Sub/Sub.cpp
        src/Operators/Sub/Sub.h
        src/Operators/Multiply/Multiply.cpp
        src/Operators/Multiply/Multiply.h
        src/Utils/Utils.cpp
        src/Utils/Utils.h)

if(MSVC)
    target_compile_options(matrix PRIVATE /W4 /WX)
else()
    target_compile_options(matrix PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wvla -Werror)
endif()

# GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        tests/MatrixTest.cpp
        src/Matrix/Matrix.cpp
        src/Matrix/Matrix.hpp
        src/Operators/Operator.h
        src/Operators/Add/Add.h
        src/Operators/Add/Add.cpp
        src/Operators/Multiply/Multiply.h
        src/Operators/Multiply/Multiply.cpp
        src/Operators/Sub/Sub.h
        src/Operators/Sub/Sub.cpp
        src/Utils/Utils.h
        src/Utils/Utils.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)