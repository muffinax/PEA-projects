#include <iostream>
#include "TSPData.h"

using namespace std;
int main() {
    srand(time(NULL));

    TSPData tspData = TSPData();
    tspData.showData();
    tspData.generateAsymetricData(10,105);
    tspData.showData();
    return 0;
}
