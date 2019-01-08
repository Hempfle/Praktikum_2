//
// Team: Christopher Weber, Melanie Famao

#include <map>

#ifndef PRAKTIKUM_2_ABSTRACTNODE_H
#define PRAKTIKUM_2_ABSTRACTNODE_H

#endif //PRAKTIKUM_2_ABSTRACTNODE_H

template<class T, class E=char>
class AbstractNode {
public:

    T value;

    std::map<E, T *> nextNodes;

    AbstractNode() = default;

    AbstractNode(T value) : value(value), nextNodes() {}

    T getValue() { return value; }

    std::map<char, T *> getAllNextNodes() {
        return nextNodes;
    }

    virtual void setNewChild(E key, T *next) {
        nextNodes[key] = next;
    }

};