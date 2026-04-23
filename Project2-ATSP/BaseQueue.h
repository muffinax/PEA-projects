#ifndef PROJEKT2_ATSP_BASEQUEUE_H
#define PROJEKT2_ATSP_BASEQUEUE_H

#include "NodeState.h"

class BaseQueue {
protected:
    Node* first;
    int size;

public:
    BaseQueue() : first(nullptr), size(0) {}

    virtual ~BaseQueue() {
        while (!isEmpty()) {
            TspState* state = pop();
            // Clearing whole state in matrix
            if (state->matrix != nullptr) {
                for (int i = 0; i < state->matrixSize; i++) {
                    delete[] state->matrix[i];
                }
                delete[] state->matrix;
            }
            delete[] state->path;
            delete[] state->visited;
            delete state;
        }
    }

    bool isEmpty() {
        return first == nullptr;
    }

    int getSize() {
        return size;
    }

    // pop is the same for every other queue
    TspState* pop() {
        if (first == nullptr) return nullptr;

        Node* tmp = first;
        TspState* result = first->state;

        first = first->next;
        delete tmp;
        size--;

        return result;
    }

    // every algorithm have different
    virtual void push(TspState* newState) = 0;
};

#endif //PROJEKT2_ATSP_BASEQUEUE_H
