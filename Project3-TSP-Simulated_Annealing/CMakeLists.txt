cmake_minimum_required(VERSION 3.26)
project(Project3_TSA_Tabu_Search)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project3_TSA_Tabu_Search main.cpp
        TSPData.h
        TSPData.cpp
        SimulatedAnnealingAlgorithm.h
        SimulatedAnnealingAlgorithm.cpp)
