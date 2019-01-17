//
// Created by Mel on 13.01.2019.
//

#ifndef PRAKTIKUM_2_ABSTRACTNODE2_H
#define PRAKTIKUM_2_ABSTRACTNODE2_H

template<class T, class E=char>
class AbstractNode2 {
public:
    bool isLeaf;

    AbstractNode2() = default;
    AbstractNode2(bool isItLeaf) : isLeaf(isItLeaf) {};
    virtual ~AbstractNode2() = default;

};


#endif //PRAKTIKUM_2_ABSTRACTNODE2_H
