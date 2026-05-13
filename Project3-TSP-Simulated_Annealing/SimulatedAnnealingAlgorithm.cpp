#include <iostream>
#include <chrono>
#include <climits>
#include <cmath>
#include "SimulatedAnnealingAlgorithm.h"

using namespace std;
using namespace std::chrono;
SimulatedAnnealingAlgorithm::SimulatedAnnealingAlgorithm(){
    finalPath = nullptr;
    currentPath = nullptr;
    candidatePath = nullptr;
    startingPath = nullptr;
    cities = 0;

    length = 0;
    finalLength=0;
    startingLength=0;

    t = 0;
    alpha = 0.99;
    l = 0;

    maxTime = 15*60;
    time = 0;
}

SimulatedAnnealingAlgorithm::~SimulatedAnnealingAlgorithm() {
    clear();
}

void SimulatedAnnealingAlgorithm::set_default(TSPData& data){
    t = 100000;
    alpha=0.99;
    if(cities>0) {
        l = calculateTransformations(data.getCities());
        t = calculateInitialTemperature(data);
    }
    else {
        l = 0;
        t=0;
    }
}

void SimulatedAnnealingAlgorithm::run(TSPData& data) {
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (t <= 0)     t = calculateInitialTemperature(data);
    if (l <= 0)     l = calculateTransformations(cities);

    if (startingPath == nullptr) {
        randStartingPath(data);
    }

    //Memory:
    if (currentPath != nullptr) delete[] currentPath;
    if (candidatePath != nullptr) delete[] candidatePath;
    if (finalPath != nullptr) delete[] finalPath;
    currentPath = new int[cities];
    candidatePath = new int[cities];
    finalPath = new int[cities];

    //saving starting point as current and final at the beginning
    for (int i = 0; i < cities; i++) {
        currentPath[i] = startingPath[i];
        finalPath[i] = startingPath[i];
    }
    length = startingLength;
    finalLength = startingLength;

    double currentTemp = this->t;   //temperature copy

    time=0;
    auto start = high_resolution_clock::now();     //starting time

    //Temperature almost 0 or timeout
    while (currentTemp > 0.0001) {

        //Markow
        for (int step = 0; step < l; step++) {

            //homogenic markow - result depends on newest try
            for (int i = 0; i < cities; i++) {
                candidatePath[i] = currentPath[i];
            }

            //changing two cities
            generateNeighbor(candidatePath);

            int candidateLength = calculatePathLength(data, candidatePath);

            //Delta
            int delta = candidateLength - length;

            //Checking if new is better
            if (delta < 0) {
                //When new is better - always accept
                length = candidateLength;
                for (int i = 0; i < cities; i++) currentPath[i] = candidatePath[i]; //saving as new result

                //if it's the best found path, save it as final
                if (length < finalLength) {
                    finalLength = length;
                    for (int i = 0; i < cities; i++) finalPath[i] = currentPath[i];
                }
            }
            else {
                //calculating probability to accept
                double p = exp(-delta / currentTemp);
                double randomValue = (double)rand() / RAND_MAX;

                if (randomValue < p) {
                    // Accept
                    length = candidateLength;
                    for (int i = 0; i < cities; i++) currentPath[i] = candidatePath[i];
                }
            }
        }

        //cooling down
        currentTemp = calculatingCoolingRate(currentTemp);

        // checking time
        auto current_time = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(current_time - start);
        if (duration.count() >= maxTime) {
            break; // Przerywamy pętle, czas minął!
        }
    }

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();
}

void SimulatedAnnealingAlgorithm::randStartingPath(TSPData& data) {
    this->cities = data.getCities();
    if(cities<=0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (startingPath != nullptr) delete[] startingPath;
    startingPath = new int[cities];

    for(int i = 0; i < cities; i++) {
        startingPath[i] = i;
    }

    //fisher-yates shuffle
    //without 0 -> 0 is always starting point
    for(int i = cities - 1; i > 0; i--) {
        int j = rand() % i + 1;

        //Swaping cities in i and j places
        int temp = startingPath[i];
        startingPath[i] = startingPath[j];
        startingPath[j] = temp;
    }

    startingLength= calculatePathLength(data, startingPath);
}

void SimulatedAnnealingAlgorithm::minNearestStartingPath(TSPData& data){
    this->cities = data.getCities();
    if(cities<=0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (startingPath != nullptr) delete[] startingPath;
    startingPath = new int[cities];
    startingLength = INT_MAX;

    if (currentPath != nullptr) delete[] currentPath;
    currentPath = new int[cities];

    int** map = data.getPaths();
    bool* visited = new bool[cities];

    length=0;

    for (int i = 0; i < cities; i++){
        for(int k = 0; k < cities; k++) {
            visited[k] = false;
        }

        int currentCity = i;
        visited[i] = true;
        currentPath[0] = currentCity;
        length=0;

        for (int step=1;step<cities;step++){
            //seting max value
            int nearestCity = -1;
            int minDistance = INT_MAX;

            for(int j=0;j<cities;j++){
                if(!visited[j] && map[currentCity][j]<minDistance){
                    nearestCity=j;
                    minDistance=map[currentCity][j];
                }
            }
            length += minDistance;
            currentCity=nearestCity;
            visited[nearestCity]=true;
            currentPath[step]=currentCity;
        }
        length += map[currentCity][i];
        if(length<startingLength){
            startingLength = length;
            for(int k = 0; k < cities; k++){
                startingPath[k] = currentPath[k];
            }
        }
    }
    delete[] visited;
}

void SimulatedAnnealingAlgorithm::maxNearestStartingPath(TSPData& data){
    this->cities = data.getCities();
    if(cities<=0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    if (startingPath != nullptr) delete[] startingPath;
    startingPath = new int[cities];
    startingLength = -1;

    if (currentPath != nullptr) delete[] currentPath;
    currentPath = new int[cities];

    int** map = data.getPaths();
    bool* visited = new bool[cities];

    length=0;

    for (int i = 0; i < cities; i++){
        for(int k = 0; k < cities; k++) {
            visited[k] = false;
        }

        int currentCity = i;
        visited[i] = true;
        currentPath[0] = currentCity;
        length=0;

        for (int step=1;step<cities;step++){
            //seting min value
            int nearestCity = -1;
            int maxDistance = -1;

            for(int j=0;j<cities;j++){
                if(!visited[j] && map[currentCity][j] > maxDistance){
                    if(map[0][0]!=0){
                        if(map[currentCity][j] < map[0][0]){
                            nearestCity=j;
                            maxDistance=map[currentCity][j];
                        }
                    }
                    else{
                        nearestCity=j;
                        maxDistance=map[currentCity][j];
                    }
                }
            }
            length += maxDistance;
            currentCity=nearestCity;
            visited[nearestCity]=true;
            currentPath[step]=currentCity;
        }
        length += map[currentCity][i];
        if(length>startingLength){
            startingLength = length;
            for(int k = 0; k < cities; k++){
                startingPath[k] = currentPath[k];
            }
        }
    }
    delete[] visited;
}

int SimulatedAnnealingAlgorithm::calculatePathLength(TSPData& data, int* path){
    int cost = 0;
    int** matrix = data.getPaths();

    for (int i = 0; i < cities - 1; i++) {
        int edgeCost = matrix[path[i]][path[i+1]];
        if (edgeCost == -1) return 100000000; // Path cant be finished
        cost += edgeCost;
    }
    // Return cost
    int returnEdge = matrix[path[cities - 1]][path[0]];
    if (returnEdge == -1) return 100000000; // Path cant return to start

    return cost + returnEdge;
}

double SimulatedAnnealingAlgorithm::calculatingCoolingRate(double tk) {
    return tk*alpha;
}

int SimulatedAnnealingAlgorithm::calculateTransformations(int cit){
    return (cit*(cit-1))/2;
}

void SimulatedAnnealingAlgorithm::generateNeighbor(int* path) {
    int index1 = rand() % cities;
    int index2 = rand() % (cities-1);

    if(index1 <= index2)    index2++;

    int tmp=path[index1];
    path[index1]=path[index2];
    path[index2]=tmp;
}

void SimulatedAnnealingAlgorithm::clear() {
    if (finalPath != nullptr) {
        delete[] finalPath;
        finalPath = nullptr;
    }
    if (currentPath != nullptr) {
        delete[] currentPath;
        currentPath = nullptr;
    }
    if (startingPath != nullptr) {
        delete[] startingPath;
        startingPath = nullptr;
    }
    if (candidatePath != nullptr) {
        delete[] candidatePath;
        candidatePath = nullptr;
    }
    cities = 0;
    length = 0;
    finalLength = 0;
    startingLength = 0;
}

double SimulatedAnnealingAlgorithm::calculateInitialTemperature(TSPData& data) {
    int maxEdge = 0;
    int minEdge = INT_MAX;
    int** matrix = data.getPaths();

    for(int i = 0; i < cities; i++) {
        for(int j = 0; j < cities; j++) {
            // looking for max and min value
            if(i != j) {
                if(matrix[i][j] > maxEdge) {
                    maxEdge = matrix[i][j];
                }
                if(matrix[i][j] < minEdge) {
                    minEdge = matrix[i][j];
                }
            }
        }
    }

    //When all values are 0
    if (maxEdge == minEdge) {
        return 100.0;
    }

    return 100.0 * (maxEdge - minEdge);
}
