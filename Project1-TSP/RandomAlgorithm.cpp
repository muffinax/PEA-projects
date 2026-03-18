#include <chrono>
#include <climits>
#include "RandomAlgorithm.h"

using namespace std;
using namespace std::chrono;
RandomAlgorithm::RandomAlgorithm():Algorithm(){
    currentPath = nullptr;
}

RandomAlgorithm::~RandomAlgorithm() {
    if (currentPath != nullptr) {
        delete[] currentPath;
        currentPath = nullptr;
    }
}

void RandomAlgorithm::run(TSPData& data) {
    this->cities = data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    //clearing old tables
    if (currentPath != nullptr) delete[] currentPath;
    if (finalPath != nullptr) delete[] finalPath;

    //allocating memory
    currentPath = new int[cities];
    for(int i = 0; i < cities; i++) {       //preparing table to shuffle
        currentPath[i] = i;
    }
    finalPath = new int[cities];
    length = INT_MAX;   //looking for smaller costs
    time=0;
    int numberOfTries = 10 * cities;

    auto start = high_resolution_clock::now();     //starting time

    for(int i = 0; i < numberOfTries; i++){
        oneRun();               //creating random path
        int currentCost = calculatePathLength(data,currentPath);    //calculating cost
        if (currentCost < length) {     //if current path is faster - save it as final path
            length = currentCost;
            for (int j = 0; j < cities; j++) {
                finalPath[j] = currentPath[j];
            }
        }
    }

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();

}

void RandomAlgorithm::oneRun() {
    if(cities<=0){
        cout<<"Error - no cities to connect"<<endl;
        return;
    }

    //fisher-yates shuffle
    //without 0 - 0 is always starting point
    for(int i = cities - 1; i > 0; i--) {
        int j = rand() % i + 1;

        //Swaping cities in i and j places
        int temp = currentPath[i];
        currentPath[i] = currentPath[j];
        currentPath[j] = temp;
    }
}