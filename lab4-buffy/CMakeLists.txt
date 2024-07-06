cmake_minimum_required(VERSION 3.22)
project(POA_Labo4)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(buffy
        src/character/Humanoid.cpp src/character/Humanoid.hpp
        src/character/Human.cpp src/character/Human.hpp
        src/character/Vampire.cpp src/character/Vampire.hpp
        src/character/Buffy.cpp src/character/Buffy.hpp
        src/gui/FieldDisplayer.hpp src/gui/FieldDisplayer.cpp
        src/action/Action.cpp src/action/Action.hpp
        src/action/Kill.cpp src/action/Kill.hpp
        src/action/Move.cpp src/action/Move.hpp
        src/action/Transform.cpp src/action/Transform.hpp
        src/Field.cpp src/Field.hpp
        src/Game.hpp src/Game.cpp
        src/Constants.hpp
        src/main.cpp src/Utils.hpp src/FieldImpl.hpp)
