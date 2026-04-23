#ifndef PROJEKT2_ATSP_CONTAINERS_H
#define PROJEKT2_ATSP_CONTAINERS_H

#include "NodeState.h"
#include "BaseQueue.h"

class DFSStack : public BaseQueue {
public:
    // pushing state at the beginging
    void push(TspState* newState) override {
        Node* newNode = new Node;

        newNode->state = newState;
        newNode->next = first;

        first = newNode;
        size++;
    }
};

class BFSQueue : public BaseQueue {
private:
    Node* last;     //Node at the end

public:
    BFSQueue() : BaseQueue(), last(nullptr) {}

    void push(TspState* newState) override {
        //New state goes to the end of queue
        Node* newNode = new Node;
        newNode->state = newState;
        newNode->next = nullptr;

        //if empty
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
        size++;
    }
};

class PriorityQueue : public BaseQueue {
public:
    void push(TspState* newState) override {
        Node* newNode = new Node;
        newNode->state = newState;
        newNode->next = nullptr;
        size++;

        //if empty of if current LB is the lowest - add at beginning of queue
        if (first == nullptr || newState->currentLB < first->state->currentLB) {
            newNode->next = first;
            first = newNode;
            return;
        }

        Node* current = first;
        Node* prev = nullptr;
        //looking fwhere to place new Node
        while (current != nullptr && current->state->currentLB <= newState->currentLB) {
            prev = current;
            current = current->next;
        }

        newNode->next = current;
        prev->next = newNode;
    }
};

#endif //PROJEKT2_ATSP_CONTAINERS_H