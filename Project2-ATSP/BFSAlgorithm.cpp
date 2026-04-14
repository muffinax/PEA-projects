#include "BFSAlgorithm.h"
#include <climits>
#include <chrono>

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
    length = INT_MAX;
    time=0;

    auto start = high_resolution_clock::now();     //starting time

    //preparing root
    TspState* v = new TspState;
    v->currentCity = startingCity;
    v->currentCost = 0;
    v->visitedCount = 1;
    v->path = new int[cities];
    v->path[0] = startingCity;
    v->visited = new bool[cities];
    for (int i = 0; i < cities; i++) {
        v->visited[i] = false;
    }
    v->visited[startingCity] = true;

    // Root into the queue
    openList.push(v);

    while (!openList.isEmpty()) {
        TspState* currentState=openList.pop();

        //If it reached last point then adding cost from last to first point (if exists)
        if(currentState->visitedCount==cities){
            int returnCost = data.getCost(currentState->currentCity, startingCity);

            if (returnCost != -1 && currentState->currentCost + returnCost < length) {
                length = currentState->currentCost + returnCost; //saving new shortest path

                //Saving path
                for (int i = 0; i < cities; i++) {
                    finalPath[i] = currentState->path[i];
                }
            }
        }
        else if (currentState->currentCost < length) {
            int visiting=currentState->currentCity;
            for(int i=1; i<cities; i++){
                if(!currentState->visited[i] && data.getCost(visiting, i) != -1){
                    //Creating new state
                    TspState* childState = new TspState;
                    childState->currentCity = i;
                    childState->currentCost = currentState->currentCost + data.getCost(visiting, i);
                    childState->visitedCount = currentState->visitedCount + 1;

                    //Copy data to path
                    childState->path = new int[cities];
                    childState->visited = new bool[cities];
                    for (int j = 0; j < cities; j++) {
                        childState->path[j] = currentState->path[j];
                        childState->visited[j] = currentState->visited[j];
                    }

                    childState->path[childState->visitedCount - 1] = i;
                    childState->visited[i] = true;
                    openList.push(childState);
                }
            }
        }

        delete[] currentState->path;
        delete[] currentState->visited;
        delete currentState;
    }

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();
}