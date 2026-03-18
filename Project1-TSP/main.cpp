#include <iostream>
#include "TSPData.h"
#include "RandomAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include "NNAlgorithm.h"

using namespace std;
int main() {
    srand(time(NULL));

    TSPData tspData = TSPData();
    tspData.generateAsymetricData(10,105);
    tspData.showData();

//    BruteForceAlgorithm randomAlgorithm = BruteForceAlgorithm();
//    randomAlgorithm.run(tspData);
//    randomAlgorithm.showResult();

//    RandomAlgorithm randomAlgorithm = RandomAlgorithm();
//    randomAlgorithm.run(tspData);
//    randomAlgorithm.showResult();

    NNAlgorithm randomAlgorithm = NNAlgorithm();
    randomAlgorithm.run(tspData);
    randomAlgorithm.showResult();

    return 0;
}
