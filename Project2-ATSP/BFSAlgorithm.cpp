#include "BFSAlgorithm.h"
#include "RNNAlgorithm.h"
#include "LowerBound.h"
#include "OpenList.h"
#include <climits>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

void BFSAlgorithm::run(TSPData& data){
    this->startingCity = 0;
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (finalPath != nullptr) delete[] finalPath;
    finalPath = new int[cities];
    time = 0;

    auto startTimer = high_resolution_clock::now();     // starting time

    //upper bound
    RNNAlgorithm rnna;
    rnna.run(data);
    this->length = rnna.getLength();
    for(int i = 0; i < cities; i++) {
        this->finalPath[i] = rnna.getFinalPath()[i];
    }

    LowerBound lb;

    //lower bound
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

    //Queue
    BFSQueue openList;

    //adding first state is ub isn't optimal solution
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

        openList.push(rootState);
    } else {
        //if ub is optimal - clearing matrix
        for (int i = 0; i < cities; i++) delete[] rootMatrix[i];
        delete[] rootMatrix;
    }

    // BFS
    while (!openList.isEmpty()) {

        // Timer 5min!
        auto current_time = high_resolution_clock::now();
        auto elapsed_seconds = duration_cast<seconds>(current_time - startTimer).count();
        if (elapsed_seconds >= 300) {
            time = -1;
            break;
        }

        TspState* currentState = openList.pop();

        // when lb>=up - stop checking this branch
        if (currentState->currentLB >= length) {
            for(int i = 0; i < cities; i++) delete[] currentState->matrix[i];
            delete[] currentState->matrix;
            delete[] currentState->path;
            delete[] currentState->visited;
            delete currentState;
            continue;
        }

        // when reached the end of a branch
        if(currentState->visitedCount == cities) {
            int returnCost = data.getCost(currentState->currentCity, startingCity);

            if (returnCost != -1) {
                // counting exact cost of this branch
                int exactCost = 0;
                for(int i = 0; i < cities - 1; i++) {
                    exactCost += data.getCost(currentState->path[i], currentState->path[i+1]);
                }
                exactCost += returnCost;

                //if cost is < upperbound - updating upperbound
                if (exactCost < length) {
                    length = exactCost;
                    for (int i = 0; i < cities; i++) {
                        finalPath[i] = currentState->path[i];
                    }
                }
            }
        }
        else {  //(not at the end of the branch)
            int visiting = currentState->currentCity;

            // generate children
            for(int nextCity = 0; nextCity < cities; nextCity++){

                // checking if path exist and city is not visited
                if(!currentState->visited[nextCity] && currentState->matrix[visiting][nextCity] != INT_MAX) {

                    int costToMove = currentState->matrix[visiting][nextCity];
                    int** childMatrix = lb.copyMatrix(currentState->matrix, cities);

                    //calculating lb for child
                    int reductionCost = lb.reduceLowerBound(childMatrix, cities, visiting, nextCity, startingCity);
                    int childLB = currentState->currentLB + costToMove + reductionCost;

                    // OPTIMALISTAION - only adding path if it can be better than ub
                    if (childLB < length) {
                        TspState* childState = new TspState;
                        childState->matrix = childMatrix;
                        childState->matrixSize = cities;
                        childState->currentCity = nextCity;
                        childState->currentLB = childLB;
                        childState->visitedCount = currentState->visitedCount + 1;

                        // saving children
                        childState->path = new int[cities];
                        childState->visited = new bool[cities];
                        for (int j = 0; j < cities; j++) {
                            childState->path[j] = currentState->path[j];
                            childState->visited[j] = currentState->visited[j];
                        }

                        childState->path[childState->visitedCount - 1] = nextCity;
                        childState->visited[nextCity] = true;

                        openList.push(childState);
                    } else {
                        // child is hopeless - we are deleting it
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

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - startTimer);   //calculating time
    if (time != -1) time = duration.count();
}