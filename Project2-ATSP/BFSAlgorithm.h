#ifndef PROJEKT2_ATSP_BFSALGORITHM_H
#define PROJEKT2_ATSP_BFSALGORITHM_H

#include "Algorithm.h"
#include "OpenList.h"

class BFSAlgorithm: public Algorithm {
private:
    int startingCity;
    OpenList openList;

public:
    BFSAlgorithm(){}
    ~BFSAlgorithm() override{}
    void run(TSPData& data) override;
};


#endif //PROJEKT2_ATSP_BFSALGORITHM_H
