#include <iostream>
#include "TSPData.h"

using namespace std;
int main() {
    TSPData tspData = TSPData();
    tspData.showData();
    tspData.getDataFromFile("tsp_10.txt");
    tspData.showData();
    return 0;
}
