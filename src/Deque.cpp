#include <DataStructs/Deque.h>

template <typename T>
Deque<T>::Deque() {
    front_node = nullptr;
    back_node = nullptr;
    size = 0;
}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
T Deque<T>::front() {
    if (front_node != nullptr)
        return front_node->element;
    return T();
}

template <typename T>
T Deque<T>::back() {
    if (back_node != nullptr)
        return back_node->element;
    return T();
}

template <typename T>
int Deque<T>::getSize() {
    return size;
}

template <typename T>
bool Deque<T>::empty() {
    return size == 0;
}

template <typename T>
void Deque<T>::clear() {
    Node* current;
    Node* next;
    current = back_node;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    front_node = nullptr;
    back_node = nullptr;
    size = 0;
}

template <typename T>
void Deque<T>::appendBack(T element) {
    Node* newNode = new Node();
    newNode->element = element;
    newNode->prev = nullptr;
    newNode->next = back_node;
    if (back_node == nullptr)
        front_node = newNode;
    else
        back_node->prev = newNode;
    back_node = newNode;
    size++;
}

template <typename T>
T Deque<T>::popFront() {
    if (front_node == nullptr || empty())
        return T();
    
    Node* prev = front_node->prev;
    T to_return = front_node->element;
    if (prev != nullptr) {
        prev->next = nullptr;
        delete front_node;
        front_node = prev;
    }
    else {
        delete front_node;
        front_node = nullptr;
        back_node = nullptr;
    }
    size--;
    return to_return;
}

template <typename T>
void Deque<T>::appendFront(T element) {
    Node* newNode = new Node();
    newNode->element = element;
    newNode->prev = front_node;
    newNode->next = nullptr;
    if (front_node == nullptr)
        back_node = newNode;
    else
        front_node->next = newNode;
    front_node = newNode;
    size++;
}

template <typename T>
T Deque<T>::popBack() {
    if (back_node == nullptr || empty())
        return T();
    
    Node* next = back_node->next;
    T to_return = back_node->element;
    if (next != nullptr) {
        next->prev = nullptr;
        delete back_node;
        back_node = next;
    }
    else {
        delete back_node;
        front_node = nullptr;
        back_node = nullptr;
    }
    size--;
    return to_return;
}

template <typename T>
int Deque<T>::getNormalQueuePos(bool (*equalFunc)(T,T), T element) {
    if (front_node == nullptr || size == 0)
        return -1;

    Node* current;
    int i = 0;
    current = front_node;
    while (current != nullptr) {
        if (equalFunc(current->element, element))
            return i;
        current = current->prev;
        i++;
    }
    return -1;
}

template <typename T>
int Deque<T>::getInverseQueuePos(bool (*equalFunc)(T,T), T element) {
    if (back_node == nullptr || size == 0)
        return -1;

    Node* current;
    int i = 0;
    current = back_node;
    while (current != nullptr) {
        if (equalFunc(current->element, element))
            return i;
        current = current->next;
        i++;
    }
    return -1;
}

template <typename T>
int Deque<T>::count(bool (*equalFunc)(T,T), T element) {
    if (back_node == nullptr || size == 0)
        return 0;

    Node* current;
    int i = 0;
    current = back_node;
    while (current != nullptr) {
        if (equalFunc(current->element, element))
            i++;
        current = current->next;
    }
    return i;
}

template <typename T>
void Deque<T>::showDeque(void (*printFunc)(T)) {
    if (back_node == nullptr || empty())
        return;
    Node* current;
    current = back_node;
    while (current != nullptr) {
        printFunc(current->element);
        current = current->next;
    }
}

template <typename T>
void Deque<T>::print(std::vector<T>& buffer, T (*transform)(T)) {
    if (front_node == nullptr || empty())
        return;
    Node* current;
    current = front_node;
    while (current != nullptr) {
        buffer.push_back(transform(current->element));
        current = current->prev;
    }
}
