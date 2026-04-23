#ifndef PROJEKT2_ATSP_NODESTATE_H
#define PROJEKT2_ATSP_NODESTATE_H

struct TspState {
    int** matrix;       // reduced matrix for current state
    int matrixSize;
    int currentCity;
    int currentLB;      //lower bound
    int visitedCount;
    int* path;
    bool* visited;
};

struct Node {
    TspState* state;
    Node* next;
};

#endif //PROJEKT2_ATSP_NODESTATE_H
