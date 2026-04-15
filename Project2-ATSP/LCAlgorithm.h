#ifndef PROJEKT2_ATSP_LCALGORITHM_H
#define PROJEKT2_ATSP_LCALGORITHM_H

#include "Algorithm.h"
#include "PriorityQueue.h"

class LCAlgorithm: public Algorithm {
private:
    int startingCity;
    PriorityQueue priorityQueue;

public:
    LCAlgorithm(){}
    ~LCAlgorithm() override{}
    void run(TSPData& data) override;
};


#endif //PROJEKT2_ATSP_LCALGORITHM_H
