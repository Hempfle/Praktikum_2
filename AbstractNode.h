//
// Team: Christopher Weber, Melanie Famao

#include <map>

#ifndef PRAKTIKUM_2_ABSTRACTNODE_H
#define PRAKTIKUM_2_ABSTRACTNODE_H

#endif //PRAKTIKUM_2_ABSTRACTNODE_H

template <class T>
class AbstractNode {
public:

    std::map<char, T*> nextNode;

     T getNextNode(char key) {
        return nextNode.at(key);
    }

    void setNextNode(char key, T* next) {
        nextNode[key] = next;
     }

};