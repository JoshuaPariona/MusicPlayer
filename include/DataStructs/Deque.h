#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <vector>

template <typename T>
class Deque {
    private:
        struct Node {
            Node* prev;
            T element;
            Node* next;
        };
        Node* front_node;
        Node* back_node;
        int size;
    
    public:
        Deque();
        ~Deque();
        T front();
        T back();
        int getSize();
        bool empty();
        void clear();
        void appendBack(T element);
        T popFront();
        void appendFront(T element);
        T popBack();
        int getNormalQueuePos(bool (*equalFunc)(T,T), T element);
        int getInverseQueuePos(bool (*equalFunc)(T,T), T element);
        int count(bool (*equalFunc)(T,T), T element);
        void showDeque(void (*printFunc)(T));
        void print(std::vector<T>& buffer, T (*transform)(T));
};

#endif  // DEQUE_H
