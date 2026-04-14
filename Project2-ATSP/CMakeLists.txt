cmake_minimum_required(VERSION 3.26)
project(Projekt2_ATSP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt2_ATSP main.cpp
        TSPData.h
        TSPData.cpp
        DFSAlgorithm.h
        DFSAlgorithm.cpp
        Algorithm.h
        BFSAlgorithm.h
        BFSAlgorithm.cpp
        OpenList.h)
