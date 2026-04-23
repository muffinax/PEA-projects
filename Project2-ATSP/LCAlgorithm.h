#ifndef PROJEKT2_ATSP_LCALGORITHM_H
#define PROJEKT2_ATSP_LCALGORITHM_H

#include "Algorithm.h"
#include "OpenList.h"

class LCAlgorithm: public Algorithm {
private:
    int startingCity;
public:
    LCAlgorithm(){}
    ~LCAlgorithm() override{}
    void run(TSPData& data) override;
};


#endif //PROJEKT2_ATSP_LCALGORITHM_H
