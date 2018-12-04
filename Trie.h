//
// Team: Melanie Famao, Christopher Weber
//

#include <map>
#include <string>
#include "AbstractNode.h"

#ifndef PRAKTIKUM_2_TRIE_H
#define PRAKTIKUM_2_TRIE_H

#endif //PRAKTIKUM_2_TRIE_H

//TODO postorder implementieren

template <class T, class E=char>
class Trie {
public:
    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::map<const key_type, T> value_type;
    typedef T mapped_type;

    bool empty() const;
    void erase(const key_type& value);
    void clear(); // erase all


    class innerNode : AbstractNode<T> {
//jeder knoten hat eine map, bsp. e zeigt auf pointer

    };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class TrieIterator {

    };
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    typedef TrieIterator iterator;

    iterator insert(const value_type& value);
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    iterator find(const key_type& testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};