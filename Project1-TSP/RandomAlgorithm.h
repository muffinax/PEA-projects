#ifndef PROJECT1_TSP_RANDOMALGORITHM_H
#define PROJECT1_TSP_RANDOMALGORITHM_H

#include "Algorithm.h"

class RandomAlgorithm : public Algorithm{
private:
    int* currentPath;       //currently the best path
    int numberOfTries;
    void oneRun();
public:
    RandomAlgorithm();
    ~RandomAlgorithm() override;
    void run(TSPData& data) override;
    void setNumberOfTries(int n)    {numberOfTries=n;}
};


#endif //PROJECT1_TSP_RANDOMALGORITHM_H
