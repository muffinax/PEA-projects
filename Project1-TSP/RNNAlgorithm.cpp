#include "RNNAlgorithm.h"
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

RNNAlgorithm::RNNAlgorithm() : Algorithm() {
    visited = nullptr;
    currentPath = nullptr;
    currentCost=0;
}
RNNAlgorithm::~RNNAlgorithm() {
    if(visited != nullptr) {
        delete[] visited;
        visited = nullptr;
    }
    if(currentPath != nullptr) {
        delete[] currentPath;
        currentPath = nullptr;
    }
}

void RNNAlgorithm::run(TSPData &data){
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    //clearing and allocating memory
    if (finalPath != nullptr) delete[] finalPath;
    finalPath = new int[cities];
    if (visited != nullptr) delete[] visited;
    visited = new bool[cities];
    if (currentPath != nullptr) delete[] currentPath;
    currentPath = new int[cities];
    length = INT_MAX;
    time=0;

    auto start = high_resolution_clock::now();     //starting time

    for (int startCity = 0; startCity < cities; startCity++){
        //list of visited cities
        for(int i = 0; i < cities; i++) {
            visited[i] = false;
        }

        repetition(data, startCity);

        if (currentCost < length) {
            length = currentCost;
            for (int i = 0; i < cities; i++) {
                finalPath[i] = currentPath[i];
            }
        }
    }

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();

};

void RNNAlgorithm::repetition(TSPData &data, int begin) {
    int** map = data.getPaths();

    //start in "begin" city
    int currentCity = begin;
    visited[begin] = true;
    currentPath[0] = begin;
    currentCost = 0;

    //finding n-1 nearest cities
    for (int i = 1; i < cities; i++) {

        //seting max value
        int nearestCity = -1;
        int minDistance = INT_MAX;

        //checking every city
        for(int j=0;j<cities;j++){
            if(!visited[j] && map[currentCity][j]<=minDistance){
                nearestCity=j;
                minDistance=map[currentCity][j];
            }
        }
        currentCost += minDistance;
        currentCity=nearestCity;
        visited[nearestCity]=true;
        currentPath[i]=currentCity;
    }

    currentCost += map[currentCity][begin];
}