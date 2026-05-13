#include "TSPData.h"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

TSPData::TSPData() {
    this->cities=0;
    this->paths= nullptr;
}

TSPData::~TSPData() {
    clearData();
}

void TSPData::showData() {
    cout << endl;
    if(cities==0){
        cout<<"No data saved :("<<endl;
        return;
    }

    cout << "Paths table:"<<endl;
    for(int i=0;i<cities;i++){
        for(int j=0;j<cities-1;j++){
            cout << paths[i][j] <<" ";
        }
        cout << paths[i][cities-1] <<endl;
    }
    cout<<endl<<"Cities: "<<cities<<endl;
}

//getting data from file
void TSPData::getDataFromFile(const string& fileName) {
    clearData();    //clearing data before saving new
    ifstream reader(fileName);  //opening file
    bool matrixSectionFound = false;    //checking if header ended

    if (!reader.is_open()) {
        cout << "Error - file " << fileName << " doesn't exist" << endl;
        return;
    }

    string line;
    cities = 0;

    while(getline(reader, line)){
        int val;
        if(sscanf(line.c_str(), "DIMENSION: %d", &val) == 1 || sscanf(line.c_str(), "DIMENSION : %d", &val) == 1)    cities=val;
        if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            matrixSectionFound = true;
            break;
        }
    }

    //checking if file format is good
    if (!matrixSectionFound || cities <= 0) {
        cout << "Error - wrong ATSP file format (missing DIMENSION or EDGE_WEIGHT_SECTION)" << endl;
        reader.close();
        return;
    }

    paths = new int*[cities];
    for (int i = 0; i < cities; i++) {
        paths[i] = nullptr;
    }

    //getting matrix data
    for (int i = 0; i < cities; i++) {
        paths[i] = new int[cities];

        for (int j = 0; j < cities; j++) {
            if (!(reader >> paths[i][j])) {
                cout << "Error - wrong data format in matrix" << endl;
                clearData();
                reader.close();
                return;
            }
        }
    }

    cout<<"TSPData successfully saved!" << endl;
    reader.close();
}

//clears data
void TSPData::clearData() {
    if(paths != nullptr){
        for (int i = 0; i < cities; i++) {
            delete[] paths[i];
        }
        delete[] paths;
        paths = nullptr;
    }
    cities=0;
}