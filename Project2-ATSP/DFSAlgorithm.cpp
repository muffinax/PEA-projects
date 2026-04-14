#include "DFSAlgorithm.h"
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

void DFSAlgorithm::dfsRecursive(TSPData& data, int currentCity, int currentCost, int visitedCount, int* currentPath, bool* visited){
    if (visitedCount == cities) {   //When visited all cities stop

        int returnCost = data.getCost(currentCity, startingCity);

        //Checking if path from last to starting point exists & is new path better than saved one
        if (returnCost != -1 && currentCost+returnCost < length){

            //saving new shortest path
            length=currentCost+returnCost;
            for (int i = 0; i < cities; i++) {
                finalPath[i] = currentPath[i];
            }
        }
        return;
    }
    else{
        //OPTIMIZATION - If current cost is bigger than already found before then stop
        if (currentCost >= length){
            return;
        }

        for (int nextCity = 1; nextCity < cities; nextCity++){

            int costToNext = data.getCost(currentCity, nextCity);

            //Recursive goes brrt
            if(!visited[nextCity] && costToNext != -1){

                visited[nextCity] = true;
                currentPath[visitedCount] = nextCity;

                dfsRecursive(data, nextCity, currentCost+costToNext, visitedCount+1, currentPath, visited);

                //Unlocking this city for new path
                visited[nextCity] = false;
            }
        }
    }
}

void DFSAlgorithm::run(TSPData& data){
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (finalPath != nullptr) delete[] finalPath;
    finalPath = new int[cities];
    int* currentPath = new int[cities];
    bool* visited = new bool[cities];
    for (int i = 0; i < cities; i++) {
        visited[i] = false;
    }
    length = INT_MAX;
    startingCity = 0;
    time=0;

    auto start = high_resolution_clock::now();     //starting time

    visited[startingCity] = true;
    currentPath[0] = startingCity;
    dfsRecursive(data, startingCity, 0, 1, currentPath, visited);

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();

    delete[] currentPath;
    delete[] visited;
}
