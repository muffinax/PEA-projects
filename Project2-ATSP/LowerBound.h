#ifndef PROJEKT2_ATSP_LOWERBOUND_H
#define PROJEKT2_ATSP_LOWERBOUND_H

#include "TSPData.h"

class LowerBound {
public:
    LowerBound();
    ~LowerBound();

    int calculateLowerBound(int** matrix, int cities);
    int reduceLowerBound(int** reducedMatrix, int cities, int from, int to, int startCity);
    int** copyMatrix(int** source, int cities);

};


#endif //PROJEKT2_ATSP_LOWERBOUND_H
