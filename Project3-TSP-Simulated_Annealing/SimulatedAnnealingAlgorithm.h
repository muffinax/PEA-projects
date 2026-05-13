#ifndef PROJECT1_TSP_RANDOMALGORITHM_H
#define PROJECT1_TSP_RANDOMALGORITHM_H

#include "TSPData.h"

class SimulatedAnnealingAlgorithm {
private:
    int cities;           //cities

    int* finalPath;       //path of visited cities
    int* currentPath;       //currently the best path
    int* candidatePath;
    int* startingPath;

    double t;
    double alpha;
    int l;

    int finalLength;
    int startingLength;
    int length;           //sum of lengths between visited cities
    long long maxTime;
    long long time;            //time

    double calculatingCoolingRate(double tk);
    int calculatePathLength(TSPData& data, int* path);
    void generateNeighbor(int* path);
public:
    SimulatedAnnealingAlgorithm();
    ~SimulatedAnnealingAlgorithm();
    void run(TSPData& data);
    void clear();

    void randStartingPath(TSPData& data);
    void nearestStartingPath(TSPData& data);

    int calculateTransformations(int cit);

    void set_maxTime(long long mt) { maxTime = mt; }
    void set_alpha(double a) { alpha = a; }
    void set_T(double t) { this->t = t; }
    void set_L(int l) { this->l = l; }
    void set_default();

    int* get_finalPath(){return finalPath;}
    int* get_startingPath(){return startingPath;}
    int get_finalLength(){return finalLength;}
    int get_startingLength(){return startingLength;}
    double get_T(){return t;}
    double get_alpha(){return alpha;}
    int get_L(){return l;}
    long long get_maxTime(){return maxTime;}
    long long get_time(){return time;}
};


#endif //PROJECT1_TSP_RANDOMALGORITHM_H
