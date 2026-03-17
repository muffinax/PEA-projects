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
    void generateData(int cities);
    void getDataFromFile(const std::string& fileName);
    void showData();
    void clearData();
};


#endif //CLIONPROJECTS_TSPDATA_H
