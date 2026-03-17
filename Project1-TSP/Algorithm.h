#ifndef PROJECT1_TSP_ALGORITHM_H
#define PROJECT1_TSP_ALGORITHM_H

#include "TSPData.h"
#include <iostream>

//Abstract clas
class Algorithm{
protected:
    int* finalPath;       //path of visited cities
    int length;           //sum of lengths between visited cities
    long long time;            //time
    int cities;           //cities

    int calculatePathLength(TSPData& data, int* path){  //calculating cost
        int cost = 0;
        int** matrix = data.getPaths();

        for (int i = 0; i < cities - 1; i++) {
            cost += matrix[path[i]][path[i+1]];
        }

        cost += matrix[path[cities - 1]][path[0]];
        return cost;
    }

public:
    Algorithm() {
        finalPath = nullptr;
        length = 0;
        time = 0;
        cities = 0;
    }

    virtual ~Algorithm() {
        if (finalPath != nullptr) {
            delete[] finalPath;
            finalPath = nullptr;
        }
    }

    //every algorithm have different method run
    virtual void run(TSPData& data) = 0;

    virtual void showResult(){
        std::cout<<std::endl;
        std::cout<<"Algorithm result:"<<std::endl;

        if (length == 0 || finalPath == nullptr) {
            std::cout<< std::endl << "No results. Try first running the algorithm" << std::endl;
            return;
        }

        std::cout<<"Optimal path: ";
        for (int i = 0; i < cities; i++) {
            std::cout << finalPath[i] << " -> ";
        }
        std::cout << finalPath[0] << std::endl;
        std::cout<<"Length: "<<length<<std::endl;
        std::cout<<"Time: "<<time <<"ns"<<std::endl;
        std::cout<<std::endl;
    }
};

#endif //PROJECT1_TSP_ALGORITHM_H
