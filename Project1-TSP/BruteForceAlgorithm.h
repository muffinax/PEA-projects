#ifndef PROJECT1_TSP_BRUTEFORCEALGORITHM_H
#define PROJECT1_TSP_BRUTEFORCEALGORITHM_H

#include "Algorithm.h"

class BruteForceAlgorithm : public Algorithm{
private:
    int* currentPath;       //currently the best path
public:
    BruteForceAlgorithm();
    ~BruteForceAlgorithm() override;
    void run(TSPData& data) override;
};


#endif //PROJECT1_TSP_BRUTEFORCEALGORITHM_H
