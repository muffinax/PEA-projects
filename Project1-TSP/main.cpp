#include <iostream>
#include "TSPData.h"
#include "RandomAlgorithm.h"

using namespace std;
int main() {
    srand(time(NULL));

    TSPData tspData = TSPData();
    tspData.generateAsymetricData(10,105);
    tspData.showData();

    RandomAlgorithm randomAlgorithm = RandomAlgorithm();
    randomAlgorithm.run(tspData);
    randomAlgorithm.showResult();

    return 0;
}
