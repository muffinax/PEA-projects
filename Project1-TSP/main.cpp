#include <iostream>
#include "TSPData.h"
#include "RandomAlgorithm.h"
#include "BruteForceAlgorithm.h"

using namespace std;
int main() {
    srand(time(NULL));

    TSPData tspData = TSPData();
    tspData.generateAsymetricData(10,105);
    tspData.showData();

    BruteForceAlgorithm bfAlgorithm = BruteForceAlgorithm();
    bfAlgorithm.run(tspData);
    bfAlgorithm.showResult();

    return 0;
}
