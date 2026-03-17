#include "TSPData.h"
#include <iostream>
#include <fstream>
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

    if(reader.is_open()){
        if (!(reader >> cities)) {      //checking cities value
            cout<<"Error - wrong data format" << endl;
            reader.close();
            return;
        }

        paths=new int*[cities];     //pointer array - memory allocation
        for(int n=0;n<cities;n++)   paths[n]= nullptr;

        for(int i=0; i<cities; i++){
            paths[i] = new int[cities];     //memory allocation - for each row

            for(int j=0; j<cities; j++){

                if(!(reader>>paths[i][j])){   //saving values to paths
                    cout<<"Error - wrong data format" << endl;
                    clearData(); // clearing saved data
                    reader.close();
                    return;
                }
            }
        }

        for(int i=0; i<cities;i++){     //CHECKING SAVED VALUES
            for(int j=i; j<cities; j++){
                if(i==j && paths[i][j]!=-1){    //values in [i][i] must be -1
                    cout<<"WRONG value in [" << i <<"]["<<j<<"] - values on the diagonal must be -1"<<endl;
                    clearData(); // clearing saved data
                    reader.close();
                    return;
                } else if(i!=j && paths[i][j]<=0){    //paths must be > 0
                    cout<<"WRONG value in [" << i <<"]["<<j<<"] - paths must be greater than zero"<<endl;
                    clearData(); // clearing saved data
                    reader.close();
                    return;
                } else if(i!=j && paths[i][j]!=paths[j][i]) {    //it must be a graph
                    cout << "WRONG values in file - paths must be a graph" << endl;
                    clearData(); // clearing saved data
                    reader.close();
                    return;
                }
            }
        }

        cout<<"TSPData successfully saved!" << endl;
        reader.close();
    }
    else{       //file never opened
        cout<<"Error - file " << fileName << " doesn't exist"<<endl;
    }
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