#include "NNAlgorithm.h"
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

NNAlgorithm::NNAlgorithm() : Algorithm() {
    visited= nullptr;
}
NNAlgorithm::~NNAlgorithm() {
    if(visited != nullptr) {
        delete[] visited;
        visited = nullptr;
    }
}

void NNAlgorithm::run(TSPData &data) {
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }
    int** map = data.getPaths();

    //clearing and allocating memory
    if (finalPath != nullptr) delete[] finalPath;
    finalPath = new int[cities];

    if (visited != nullptr) delete[] visited;
    visited = new bool[cities];
    for(int i = 0; i < cities; i++) {
        visited[i] = false;
    }

    length=0;
    time=0;

    auto start = high_resolution_clock::now();     //starting time

    //start in 0 city
    int currentCity = 0;
    visited[0] = true;
    finalPath[0] = 0;

    //finding n-1 nearest cities
    for (int i = 1; i < cities; i++) {

        //seting max value
        int nearestCity = -1;
        int minDistance = INT_MAX;

        //avoiding 0 city
        for(int j=1;j<cities;j++){
            if(!visited[j] && map[currentCity][j]<minDistance){
                nearestCity=j;
                minDistance=map[currentCity][j];
            }
        }
        length += minDistance;
        currentCity=nearestCity;
        visited[nearestCity]=true;
        finalPath[i]=currentCity;
    }

    length += map[currentCity][0];

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();
}