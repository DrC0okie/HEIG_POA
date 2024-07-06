cmake_minimum_required(VERSION 3.15)
project(River)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main application target
add_executable(river
        src/main.cpp
        src/ControllerConstants.h
        src/Controller.cpp
        src/Controller.h
        src/Containers/Container.cpp
        src/Containers/Container.h
        src/Containers/Boat.cpp
        src/Containers/Boat.h
        src/Containers/Bank.cpp
        src/Containers/Bank.h
        src/people/Boy.cpp
        src/people/Boy.h
        src/people/Girl.cpp
        src/people/Girl.h
        src/people/Parent.cpp
        src/people/Parent.h
        src/people/Kid.cpp
        src/people/Kid.h
        src/people/Person.cpp
        src/people/Person.h
        src/people/Thief.cpp
        src/people/Thief.h
        src/people/Policeman.cpp
        src/people/Policeman.h
        src/Status.h)

if(MSVC)
    target_compile_options(river PRIVATE /W4 /WX)
else()
    target_compile_options(river PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wvla -Werror)
endif()


# GoogleTest setup
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
        src/test/ContainerTest.cpp
        src/test/RulesTest.cpp
        src/ControllerConstants.h
        src/Controller.cpp
        src/Controller.h
        src/Containers/Container.cpp
        src/Containers/Container.h
        src/Containers/Boat.cpp
        src/Containers/Boat.h
        src/Containers/Bank.cpp
        src/Containers/Bank.h
        src/people/Boy.cpp
        src/people/Boy.h
        src/people/Girl.cpp
        src/people/Girl.h
        src/people/Parent.cpp
        src/people/Parent.h
        src/people/Kid.cpp
        src/people/Kid.h
        src/people/Person.cpp
        src/people/Person.h
        src/people/Thief.cpp
        src/people/Thief.h
        src/people/Policeman.cpp
        src/people/Policeman.h
        src/Status.h)

# Compiler options for the tests
if(MSVC)
    target_compile_options(tests PRIVATE /W4 /WX /wd4834)
else()
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wvla -Wno-unused-result)
endif()

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)