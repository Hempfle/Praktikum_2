//
// Team: Christopher Weber, Melanie Famao

#include <map>

#ifndef PRAKTIKUM_2_ABSTRACTNODE_H
#define PRAKTIKUM_2_ABSTRACTNODE_H

#endif //PRAKTIKUM_2_ABSTRACTNODE_H

template <class T>
class AbstractNode {
public:

    T value;
    std::map<char, T*> nextNodes;

    AbstractNode() = default;
    AbstractNode(T value) : nextNodes(), value(value) {}

    T getNextNode(char key) {
        return nextNodes.find(key);
    }

    void setNextNode(char key, T* next) {
        nextNodes[key] = next;
     }

};