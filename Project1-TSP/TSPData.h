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
    void generateAsymetricData(int cities, int max);
    void generateSymetricData(int cities, int max);
    void getDataFromFile(const std::string& fileName);
    void showData();
    void clearData();
};


#endif //CLIONPROJECTS_TSPDATA_H
