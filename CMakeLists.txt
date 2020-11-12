cmake_minimum_required(VERSION 3.17)
project(SPL_Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SPL_Assignment1
        src/Agent.cpp
        include/Agent.h
        src/Graph.cpp
        include/Graph.h
        include/json.hpp
        src/main.cpp
        output.json
        src/Session.cpp
        include/Session.h
        src/Tree.cpp
        include/Tree.h)