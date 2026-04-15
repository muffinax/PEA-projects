cmake_minimum_required(VERSION 3.26)
project(Projekt2_ATSP)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(Projekt2_ATSP main.cpp
        TSPData.h
        TSPData.cpp
        DFSAlgorithm.h
        DFSAlgorithm.cpp
        Algorithm.h
        BFSAlgorithm.h
        BFSAlgorithm.cpp
        OpenList.h
        PriorityQueue.h
        LCAlgorithm.cpp
        LCAlgorithm.h)
