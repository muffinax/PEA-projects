cmake_minimum_required(VERSION 3.26)
project(Project1_TSP)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project1_TSP main.cpp
        TSPData.cpp
        TSPData.h
        Algorithm.h
        RandomAlgorithm.h
        RandomAlgorithm.cpp
        BruteForceAlgorithm.h
        BruteForceAlgorithm.cpp
)
