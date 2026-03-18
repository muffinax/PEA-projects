#include "BruteForceAlgorithm.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

BruteForceAlgorithm::BruteForceAlgorithm():Algorithm() {
    currentPath = nullptr;
}

BruteForceAlgorithm::~BruteForceAlgorithm() {
    if (currentPath != nullptr) {
        delete[] currentPath;
        currentPath = nullptr;
    }
}

void BruteForceAlgorithm::run(TSPData &data) {
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
    for(int i=0;i<cities;i++){
        currentPath[i]=i;
    }
    finalPath = new int[cities];
    length = INT_MAX;
    time=0;

    int* position = new int[cities-1];    //It checks if there are more permutations
    for (int i = 0; i < cities-1; i++) {    //cities-1 (without 0)
        position[i] = 0;
    }
    int i = 0;

    auto start = high_resolution_clock::now();     //starting time

    //checking first path
    length = calculatePathLength(data, currentPath);
    for (int j = 0; j < cities; j++) finalPath[j] = currentPath[j];

    while (i < cities-1) {
        if (position[i] < i) {
            int tmp;
            if (i % 2 == 0) {
                tmp=currentPath[1];
                currentPath[1]=currentPath[i+1];
                currentPath[i+1]=tmp;
            } else {
                tmp=currentPath[position[i]+1];
                currentPath[position[i]+1]=currentPath[i+1];
                currentPath[i+1]=tmp;
            }

            //Checking length of new permutations
            int currentCost = calculatePathLength(data, currentPath);
            if (currentCost < length) {
                length = currentCost;
                for (int j = 0; j < cities; j++) {
                    finalPath[j] = currentPath[j];
                }
            }

            position[i] += 1;
            i = 0;

//            for(int k=0;k<cities-2;k++){
//                cout<<position[k]<< " ";
//            }
//            cout<<position[cities-2]<<endl;
        } else {
            position[i] = 0;
            i += 1;
        }

    }

    auto end = high_resolution_clock::now();        //finish time
    auto duration = duration_cast<microseconds>(end - start);   //calculating time
    time = duration.count();

    delete[] position;
}