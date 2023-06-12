#include "DataStructs/GenericTree.h"
#include <iostream>
#include <vector>

template <typename T>
void GenericTree<T>::deleteTree(GenericTree<T>& node) {
    for (GenericTree<T>& child : node.children)
        deleteTree(child);

    node.clear();
}

template <typename T>
void GenericTree<T>::print(void (*printFunc)(T), int tab, const GenericTree<T>& node) {
    for (int i = 0; i < tab; i++)
        std::cout << "  ";

    printFunc(node.root);
    std::cout << std::endl;
    for (GenericTree<T>& child : node.children)
        print(printFunc, tab + 1, child);
}

template <typename T>
void GenericTree<T>::addChild(const T& child) {
    children.push_back(GenericTree<T>(child, this));
}

template <typename T>
bool GenericTree<T>::removeChildAt(int index) const {
    std::vector<GenericTree<T>> newChildren = {};
    if (index >= 0 && index < children.size()) {
        std::cout<<children[index].getData()<<"\n";
        for (int i = 0; i < children.size(); i++) {
            if (index == i)
                continue;   
            newChildren.push_back(children[i]);
        }
        children = newChildren;
        return true;
    }
    return false;
}

