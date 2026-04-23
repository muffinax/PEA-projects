#include <iostream>
#include <climits>
#include "LowerBound.h"

using namespace std;

LowerBound::LowerBound() {
}

LowerBound::~LowerBound() {
}

int LowerBound::calculateLowerBound(int** reducedMatrix, int cities) {
    int lowerBound = 0;

    // reducing in rows
    for(int i = 0; i < cities; i++){
        int min = INT_MAX;
        for(int j = 0; j < cities; j++){
            if(reducedMatrix[i][j] < min) min = reducedMatrix[i][j];
        }

        if(min != INT_MAX && min > 0) {
            for(int j = 0; j < cities; j++){
                if(reducedMatrix[i][j] != INT_MAX) reducedMatrix[i][j] -= min;
            }
            lowerBound += min;
        }
    }

    // reducing in columns
    for(int i = 0; i < cities; i++){
        int min = INT_MAX;
        for(int j = 0; j < cities; j++){
            if(reducedMatrix[j][i] < min) min = reducedMatrix[j][i];
        }

        if(min != INT_MAX && min > 0) {
            for(int j = 0; j < cities; j++){
                if(reducedMatrix[j][i] != INT_MAX) reducedMatrix[j][i] -= min;
            }
            lowerBound += min;
        }
    }
    return lowerBound;
}

int LowerBound::reduceLowerBound(int **reducedMatrix, int cities, int from, int to, int startCity) {
    int lowerBound = 0;

    // prevents going back
    reducedMatrix[to][startCity] = INT_MAX;

    // Erasing path visited
    for (int i = 0; i < cities; i++) {
        reducedMatrix[from][i] = INT_MAX;
        reducedMatrix[i][to] = INT_MAX;
    }

    // Again reducing rows
    for(int i = 0; i < cities; i++){
        int min = INT_MAX;
        for(int j = 0; j < cities; j++){
            if(reducedMatrix[i][j] < min) min = reducedMatrix[i][j];
        }

        if(min != INT_MAX && min > 0) {
            for(int j = 0; j < cities; j++){
                if(reducedMatrix[i][j] != INT_MAX) reducedMatrix[i][j] -= min;
            }
            lowerBound += min;
        }
    }

    // reducing in columns
    for(int i = 0; i < cities; i++){
        int min = INT_MAX;
        for(int j = 0; j < cities; j++){
            if(reducedMatrix[j][i] < min) min = reducedMatrix[j][i];
        }

        if(min != INT_MAX && min > 0) {
            for(int j = 0; j < cities; j++){
                if(reducedMatrix[j][i] != INT_MAX) reducedMatrix[j][i] -= min;
            }
            lowerBound += min;
        }
    }

    return lowerBound;
}

int** LowerBound::copyMatrix(int** source, int cities) {
    int** dest = new int*[cities];
    for (int i = 0; i < cities; i++) {
        dest[i] = new int[cities];
        for (int j = 0; j < cities; j++) {
            dest[i][j] = source[i][j];
        }
    }
    return dest;
}