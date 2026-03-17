#ifndef PROJECT1_TSP_ALGORITHM_H
#define PROJECT1_TSP_ALGORITHM_H

#include "TSPData.h"
#include <iostream>

//Abstract clas
class Algorithm{
protected:
    int* finalPath;       //path of visited cities
    int length;           //sum of lengths between visited cities
    long time;            //time
    int cities;           //cities

public:
    Algorithm() {
        finalPath = nullptr;
        length = 0;
        time = 0;
        cities = 0;
    }

    virtual ~Algorithm() {
        clearResult();
    }

    virtual void clearResult(){
        if (finalPath != nullptr) {
            delete[] finalPath;
            finalPath = nullptr;
        }
    }

    //every algorithm have different method run
    virtual void run(TSPData& data) = 0;

    virtual void showResult(){
        std::cout<<"Result:"<<std::endl;

        if (length == 0 || finalPath == nullptr) {
            std::cout<< std::endl << "No results. Try first running the algorithm" << std::endl;
            return;
        }

        std::cout<<std::endl;
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
