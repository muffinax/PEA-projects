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
    void getDataFromFile(const std::string& fileName);
    void showData();
    void clearData();
    int getCities() {return cities;}
    int** getPaths() {return paths;}
    int getCost(int from, int to) {
        if(from >= 0 && from < cities && to >= 0 && to < cities) {
            return paths[from][to];
        }
        return -1;
    }
};


#endif //CLIONPROJECTS_TSPDATA_H
