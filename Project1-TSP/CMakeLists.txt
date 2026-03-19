cmake_minimum_required(VERSION 3.26)
project(Project1_TSP)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(Project1_TSP main.cpp
        TSPData.cpp
        TSPData.h
        Algorithm.h
        RandomAlgorithm.h
        RandomAlgorithm.cpp
        BruteForceAlgorithm.h
        BruteForceAlgorithm.cpp
        NNAlgorithm.h
        NNAlgorithm.cpp
        RNNAlgorithm.h
        RNNAlgorithm.cpp
)
