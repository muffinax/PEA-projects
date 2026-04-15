#ifndef PROJEKT2_ATSP_OPENLIST_H
#define PROJEKT2_ATSP_OPENLIST_H

//state struct
struct TspState {
    int currentCity;
    int currentCost;
    int visitedCount;
    int* path;
    bool* visited;
};

//Pointers struct
struct Node {
    TspState* state;
    Node* next;
};

class OpenList{
private:
    Node* first;
    Node* last;
    int size;
public:
    OpenList(){
        first= nullptr;
        last= nullptr;
        size=0;
    }

    ~OpenList() {
        while (!isEmpty()) {
            TspState* state = pop();
            delete[] state->path;
            delete[] state->visited;
            delete state;
        }
    }

    //adding new state to the end of queue
    void push(TspState* newState){
        Node* newNode = new Node;
        newNode->state = newState;
        newNode->next = nullptr;

        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
        size++;
    }

    //taking out first state from queue
    TspState*  pop(){
        if (first== nullptr) return nullptr;

        Node* tmp = first;
        TspState* result=first->state;

        first = first->next;
        if (first == nullptr) {
            last = nullptr;
        }

        delete tmp;
        size--;

        return result;
    }

    bool isEmpty() {
        return first == nullptr;
    }

    int get_size() {
        return size;
    }
};

#endif //PROJEKT2_ATSP_OPENLIST_H
