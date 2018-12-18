//
// Created by chris on 18.12.2018.
//

#include <map>
#include <string>
#include <iterator>
#include <typeinfo>
#include <iostream>

#ifndef PRAKTIKUM_2_TESTHIT_H
#define PRAKTIKUM_2_TESTHIT_H


class testHit {

};

int main() {
std::map<int, int> testmap;
testmap[2] = 3;
testmap[5] = 4;

std::cout << typeid(testmap.begin()).name();

    return 0;
}


#endif //PRAKTIKUM_2_TESTHIT_H
