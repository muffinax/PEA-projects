#ifndef PROJEKT2_ATSP_LOWERBOUND_H
#define PROJEKT2_ATSP_LOWERBOUND_H

#include "TSPData.h"

class LowerBound {
private:
    int** reducedMatrix;
    int lowerBound;
    int cities;
    long long time;            //time

public:
    LowerBound();
    ~LowerBound();

    void countLowerBound(TSPData& data);
    void clearData();

    int getLowerBound(){return lowerBound;}
    long long getTime() {return time;}
    int getCost(int from, int to) {
        if(from >= 0 && from < cities && to >= 0 && to < cities) {
            return reducedMatrix[from][to];
        }
        return -1;
    }

};


#endif //PROJEKT2_ATSP_LOWERBOUND_H
