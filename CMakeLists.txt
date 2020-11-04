cmake_minimum_required(VERSION 3.17)
project(SPL_Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SPL_Assignment1
        Agent.cpp
        Agent.h
        config.json
        Graph.cpp
        Graph.h
        json.hpp
        main.cpp
        output.json
        Session.cpp
        Session.h
        Tree.cpp
        Tree.h)