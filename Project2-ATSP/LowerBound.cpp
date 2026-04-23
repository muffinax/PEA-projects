#include <iostream>
#include "LowerBound.h"
using namespace std;

LowerBound::LowerBound() {
    this->cities=0;
    this->reducedMatrix= nullptr;
    this->time=0;
    this->lowerBound=0;
}

LowerBound::~LowerBound() {
    clearData();
}

void LowerBound::countLowerBound(TSPData &data) {
    clearData();
    this->cities=data.getCities();
    if (cities <= 0){
        cout<<"Error - no cities"<<endl;
        return;
    }

    this->reducedMatrix = new int*[cities];
    for (int i = 0; i < cities; i++) {
        this->reducedMatrix[i] = new int[cities]; // Memory allocation
        for (int j = 0; j < cities; j++) {
            if(data.getCost(i,j) == -1 || i == j)   reducedMatrix[i][j] = INT_MAX;
            else    this->reducedMatrix[i][j] = data.getCost(i,j);
        }
    }


    //reducing in rows
    for(int i=0;i<cities;i++){
        int min=INT_MAX;
        for(int j=0;j<cities;j++){
            if(reducedMatrix[i][j]<min && reducedMatrix[i][j]>=0) min=reducedMatrix[i][j];
        }
        if(min==INT_MAX){
            cout<<"Error - path doesn't exist" << endl;
            return;
        }

        if(min > 0) {
            for(int j=0;j<cities;j++){
                if(reducedMatrix[i][j]<INT_MAX) reducedMatrix[i][j]-=min;
            }
            lowerBound+=min;
        }
    }

    //reducing in columns
    for(int i=0;i<cities;i++){
        int min=INT_MAX;
        for(int j=0;j<cities;j++){
            if(reducedMatrix[j][i]<min && reducedMatrix[j][i]>=0) min=reducedMatrix[j][i];
        }
        if(min==INT_MAX){
            cout<<"Error - path doesn't exist" << endl;
            return;
        }

        if(min > 0) {
            for(int j=0;j<cities;j++){
                if(reducedMatrix[j][i]<INT_MAX) reducedMatrix[j][i]-=min;
            }
            lowerBound+=min;
        }

    }
}

void LowerBound::clearData() {
    if(reducedMatrix != nullptr){
        for (int i = 0; i < cities; i++) {
            delete[] reducedMatrix[i];
        }
        delete[] reducedMatrix;
        reducedMatrix = nullptr;
    }
    cities=0;
    lowerBound=0;
    time=0;
}
