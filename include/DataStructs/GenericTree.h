#ifndef GENERICTREE_H
#define GENERICTREE_H

#include <iostream>
#include <vector>

template <typename T>
class GenericTree {
private:
    const T root;
    const GenericTree<T>* parent;
    mutable std::vector<GenericTree<T>> children;
    void print(void (*printFunc)(T), int tab, const GenericTree<T>& node);
    void print(std::vector<T>& buffer, int tab, const GenericTree<T>& node);

public:
    GenericTree(const T& data) : root(data), children({}), parent(nullptr) {}
    GenericTree(const T& data,const GenericTree<T>* parent) : root(data), children({}), parent(parent) {}
    ~GenericTree() {deleteTree(*this);}

    void deleteTree(GenericTree<T>& node);
    void addChild(const T& child);
    std::vector<GenericTree<T>>& getChildren() {return children;}
    T getData() {return root;}
    const GenericTree<T>* getParent() const {return parent;}

    bool removeChildAt(int index) const;

    void clear() {children.clear();}
    void print(void (*printFunc)(T)) {print(printFunc,0,*this);}
    void print(std::vector<T>& buffer) {print(buffer,0,*this);}
};

#endif  // GENERICTREE_H

