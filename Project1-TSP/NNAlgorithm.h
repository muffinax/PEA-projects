#ifndef PROJECT1_TSP_NNALGORITHM_H
#define PROJECT1_TSP_NNALGORITHM_H
#include "TSPData.h"
#include "Algorithm.h"

class NNAlgorithm: public Algorithm {
private:
    bool* visited;  //list of visited cities
public:
    NNAlgorithm();
    ~NNAlgorithm() override;

    void run(TSPData& data) override;
};


#endif //PROJECT1_TSP_NNALGORITHM_H
