#ifndef PROJEKT2_ATSP_PRIORITYQUEUE_H
#define PROJEKT2_ATSP_PRIORITYQUEUE_H

#include "OpenList.h"

class PriorityQueue {
private:
    Node* first;

public:
    PriorityQueue(){
        first = nullptr;
    }

    ~PriorityQueue(){
        while (!isEmpty()) {
            TspState* state = pop();
            delete[] state->path;
            delete[] state->visited;
            delete state;
        }
    }

    //pushing value but prioritizes the lowest values first
    void push(TspState* newState){
        Node* newNode = new Node;
        newNode->state = newState;
        newNode->next = nullptr;

        //empty queue or new element is the lowest
        if (first == nullptr || newState->currentCost < first->state->currentCost) {
            newNode->next = first;
            first = newNode;
            return;
        }

        //variable created to find "right place"
        Node* current = first;
        Node* prev = nullptr;
        while (current != nullptr && current->state->currentCost <= newState->currentCost) {
            prev = current;
            current = current->next;
        }

        //adding new element to the queue
        newNode->next = current;
        prev->next = newNode;
    }

    //giving out first value from queue
    TspState* pop(){
        if (first == nullptr) return nullptr;
        Node* tmp = first;
        TspState* result = tmp->state;
        first = first->next;
        delete tmp;
        return result;
    }

    bool isEmpty(){
        return first == nullptr;
    }
};

#endif //PROJEKT2_ATSP_PRIORITYQUEUE_H
