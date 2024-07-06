cmake_minimum_required(VERSION 3.10)
project(LabSquadron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main application target
add_executable(
        squadron
        src/main.cpp
        src/squadron/Squadron.cpp
        src/squadron/Squadron.hpp
        src/ship/Ship.cpp
        src/ship/Ship.hpp
        src/ship/cargo/CargoShip.cpp
        src/ship/cargo/CargoShip.hpp
        src/ship/TieFighter.cpp
        src/ship/TieFighter.hpp
        src/ship/TieInterceptor.cpp
        src/ship/TieInterceptor.hpp
        src/ship/cargo/StarDreadnought.cpp
        src/ship/cargo/StarDreadnought.hpp
        src/ship/cargo/ImperialShuttle.cpp
        src/ship/cargo/ImperialShuttle.hpp
        src/ship/Tie.cpp
        src/ship/Tie.hpp
        src/utils/ShipList.cpp
        src/utils/ShipList.hpp
        src/constants.hpp)

if(MSVC)
    target_compile_options(squadron PRIVATE /W4 /WX)
else()
    target_compile_options(squadron PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wvla -Werror)
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
        src/test/SquadronTest.cpp
        src/test/ShipListTest.cpp
        src/test/ShipTest.cpp
        src/squadron/Squadron.cpp
        src/squadron/Squadron.hpp
        src/ship/Ship.cpp
        src/ship/Ship.hpp
        src/ship/cargo/CargoShip.cpp
        src/ship/cargo/CargoShip.hpp
        src/ship/TieFighter.cpp
        src/ship/TieFighter.hpp
        src/ship/TieInterceptor.cpp
        src/ship/TieInterceptor.hpp
        src/ship/cargo/StarDreadnought.cpp
        src/ship/cargo/StarDreadnought.hpp
        src/ship/cargo/ImperialShuttle.cpp
        src/ship/cargo/ImperialShuttle.hpp
        src/ship/Tie.cpp
        src/ship/Tie.hpp
        src/utils/ShipList.cpp
        src/utils/ShipList.hpp
        src/constants.hpp
)

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