#ifndef PROJEKT2_ATSP_DFSALGORITHM_H
#define PROJEKT2_ATSP_DFSALGORITHM_H

#include "Algorithm.h"

class DFSAlgorithm : public Algorithm{
private:
    int startingCity;

    // Recursive function
    void dfsRecursive(TSPData& data, int currentCity, int currentCost, int visitedCount, int* currentPath, bool* visited);

public:
    DFSAlgorithm(){}
    ~DFSAlgorithm() override{}
    void run(TSPData& data) override;
};


#endif //PROJEKT2_ATSP_DFSALGORITHM_H
