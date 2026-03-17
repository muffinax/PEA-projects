#ifndef CLIONPROJECTS_TSPDATA_H
#define CLIONPROJECTS_TSPDATA_H
#include <string>

class TSPData {
private:
    int cities;
    int** paths;
public:
    TSPData();
    ~TSPData();
    void generateAsymetricData(int n, int max);
    void generateSymetricData(int cities, int max);
    void getDataFromFile(const std::string& fileName);
    void showData();
    void clearData();
    int getCities() {return cities;}
    int** getPaths() {return paths;}
};


#endif //CLIONPROJECTS_TSPDATA_H
