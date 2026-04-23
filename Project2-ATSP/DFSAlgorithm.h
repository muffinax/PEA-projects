#ifndef PROJEKT2_ATSP_DFSALGORITHM_H
#define PROJEKT2_ATSP_DFSALGORITHM_H

#include <chrono>
#include "Algorithm.h"
#include "LowerBound.h"

class DFSAlgorithm : public Algorithm{
private:
    int startingCity;
public:
    DFSAlgorithm(){}
    ~DFSAlgorithm() override{}
    void run(TSPData& data) override;
};


#endif //PROJEKT2_ATSP_DFSALGORITHM_H
