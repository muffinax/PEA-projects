#include "DFSAlgorithm.h"
#include "RNNAlgorithm.h"
#include "LowerBound.h"
#include "OpenList.h"
#include <climits>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

void DFSAlgorithm::run(TSPData& data) {
    this->startingCity = 0;
    this->cities = data.getCities();
    if (cities <= 0) {
        cout << "Error - no cities to connect" << endl;
        return;
    }

    if (finalPath != nullptr) delete[] finalPath;
    finalPath = new int[cities];
    time = 0;

    auto startTimer = high_resolution_clock::now();

    //Upper Bound
    RNNAlgorithm rnna;
    rnna.run(data);
    this->length = rnna.getLength();
    for(int i = 0; i < cities; i++) {
        this->finalPath[i] = rnna.getFinalPath()[i];
    }

    //Lower Bound
    LowerBound lb;
    int** rootMatrix = new int*[cities];
    for(int i = 0; i < cities; i++) {
        rootMatrix[i] = new int[cities];
        for(int j = 0; j < cities; j++) {
            int cost = data.getCost(i, j);
            if(cost == -1 || i == j) rootMatrix[i][j] = INT_MAX;
            else rootMatrix[i][j] = cost;
        }
    }

    int rootLB = lb.calculateLowerBound(rootMatrix, cities);
    DFSStack dfsStack; // Stack

    //crearing first state and pushing to the stack
    if (rootLB < this->length) {
        TspState* rootState = new TspState;
        rootState->matrix = rootMatrix;
        rootState->matrixSize = cities;
        rootState->currentCity = startingCity;
        rootState->currentLB = rootLB;
        rootState->visitedCount = 1;

        rootState->path = new int[cities];
        rootState->path[0] = startingCity;

        rootState->visited = new bool[cities];
        for (int i = 0; i < cities; i++) rootState->visited[i] = false;
        rootState->visited[startingCity] = true;

        dfsStack.push(rootState);
    } else {
        // lb >= ub !!!
        for (int i = 0; i < cities; i++) delete[] rootMatrix[i];
        delete[] rootMatrix;
    }

    // DFS
    while (!dfsStack.isEmpty()) {

        auto current_time = high_resolution_clock::now();
        auto elapsed_seconds = duration_cast<seconds>(current_time - startTimer).count();
        if (elapsed_seconds >= 300) {
            time = -1; // Time-out (5min)
            break;
        }

        TspState* currentState = dfsStack.pop(); // analysing state from stack

        // optimisation - if lb >= ub (length = ub)
        if (currentState->currentLB >= length) {
            for(int i = 0; i < cities; i++) delete[] currentState->matrix[i];
            delete[] currentState->matrix;
            delete[] currentState->path;
            delete[] currentState->visited;
            delete currentState;
            continue;
        }

        // if its the end of the branch
        if (currentState->visitedCount == cities) {
            int returnCost = data.getCost(currentState->currentCity, startingCity);

            if (returnCost != -1) {
                int exactCost = 0;
                for(int i = 0; i < cities - 1; i++) {
                    exactCost += data.getCost(currentState->path[i], currentState->path[i+1]);
                }
                exactCost += returnCost;

                if (exactCost < length) {
                    length = exactCost;
                    for (int i = 0; i < cities; i++) {
                        finalPath[i] = currentState->path[i];
                    }
                }
            }
        }
        else {
            int visiting = currentState->currentCity;

            //generating children
            for (int nextCity = cities - 1; nextCity >= 0; nextCity--) {

                if (!currentState->visited[nextCity] && currentState->matrix[visiting][nextCity] != INT_MAX) {

                    int costToMove = currentState->matrix[visiting][nextCity];
                    int** childMatrix = lb.copyMatrix(currentState->matrix, cities);

                    int reductionCost = lb.reduceLowerBound(childMatrix, cities, visiting, nextCity, startingCity);
                    int childLB = currentState->currentLB + costToMove + reductionCost;

                    if (childLB < length) {
                        TspState* childState = new TspState;
                        childState->matrix = childMatrix;
                        childState->matrixSize = cities;
                        childState->currentCity = nextCity;
                        childState->currentLB = childLB;
                        childState->visitedCount = currentState->visitedCount + 1;

                        childState->path = new int[cities];
                        childState->visited = new bool[cities];
                        for (int j = 0; j < cities; j++) {
                            childState->path[j] = currentState->path[j];
                            childState->visited[j] = currentState->visited[j];
                        }

                        childState->path[childState->visitedCount - 1] = nextCity;
                        childState->visited[nextCity] = true;

                        //pushing children on stack
                        dfsStack.push(childState);
                    } else {
                        for(int i = 0; i < cities; i++) delete[] childMatrix[i];
                        delete[] childMatrix;
                    }
                }
            }
        }

        // clearing
        for(int i = 0; i < cities; i++) delete[] currentState->matrix[i];
        delete[] currentState->matrix;
        delete[] currentState->path;
        delete[] currentState->visited;
        delete currentState;
    }

    // clearing after time-out
    if (time == -1) {
        while(!dfsStack.isEmpty()){
            TspState* leftover = dfsStack.pop();
            for(int i = 0; i < cities; i++) delete[] leftover->matrix[i];
            delete[] leftover->matrix;
            delete[] leftover->path;
            delete[] leftover->visited;
            delete leftover;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - startTimer);
    if (time != -1) time = duration.count();
}