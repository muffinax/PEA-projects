#ifndef PROJECT1_TSP_RNNALGORITHM_H
#define PROJECT1_TSP_RNNALGORITHM_H
#include "TSPData.h"
#include "Algorithm.h"

class RNNAlgorithm: public Algorithm {
private:
    int* currentPath;
    bool* visited;
    int currentCost;
    void repetition(TSPData& data, int begin);
public:
    RNNAlgorithm();
    ~RNNAlgorithm() override;

    void run(TSPData& data) override;
};


#endif //PROJECT1_TSP_RNNALGORITHM_H
