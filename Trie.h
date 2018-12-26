//
// Team: Melanie Famao, Christopher Weber
//

#include <map>
#include <string>
#include <stack>
#include "AbstractNode.h"

#ifndef PRAKTIKUM_2_TRIE_H
#define PRAKTIKUM_2_TRIE_H

#endif //PRAKTIKUM_2_TRIE_H

//TODO postorder implementieren, //Folien steht Stack als Pfad verwenden, nur für die Anzeige notwendig?

class innerNode;
class leafNode;

template<class T, class E=char>
class Trie {
public:
    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::map<const key_type, T> value_type;
    typedef T mapped_type;

    
    innerNode* startRoot;

    Trie() = default;


    bool empty() const;

    void erase(const key_type &value);

    void clear(); // erase all


    class innerNode : AbstractNode<T> {
//jeder knoten hat eine map, bsp. e zeigt auf pointer
    innerNode() = default;
    innerNode(innerNode* childPointer): AbstractNode<innerNode*>(childPointer) {};

    };

    class leafNode : AbstractNode<T> {
        leafNode() = default;
        leafNode(key_type valueLeaf): AbstractNode<key_type>(valueLeaf) {};

    };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    class postorderTreeTraversal {
    public:
        typedef AbstractNode<T> node;
        typedef postorderTreeTraversal iterator;
        typedef typename std::map<E, node>::iterator mapIterator;

        typedef std::stack<std::pair<mapIterator, mapIterator>> stack;

        node *root;
        stack current;

        postorderTreeTraversal(node *root) : root(root) {
            current.push(std::make_pair(root->nextNodes.begin(), root->nextNodes.end()));
        };

        iterator &operator=(const iterator &itr) {
            root = itr.root;
            current = itr.current;
            return *this;
        }

        bool operator==(const iterator &itr) {
            return current == itr.current && root == itr.root;
        }

        bool operator!=(const iterator &itr) { return !operator==(itr); }

        T &operator*() {
            std::pair<mapIterator, mapIterator> tmp = current.top();

            if (tmp.first != tmp.second) {
                mapIterator tmpMapIterator = tmp.first;
                return 0;
            }
        }

        iterator &operator++() { // prefix

        }

        iterator operator++(int) { // postfix
            iterator clone(*this);
            operator++();
            return clone;
        }

        void slideLeft() {

        }

    };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    typedef postorderTreeTraversal iterator;

    iterator insert(const value_type &value);

    iterator lower_bound(const key_type &testElement); // first element >= testElement
    iterator upper_bound(const key_type &testElement); // first element > testElement
    iterator find(const key_type &testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();

};

template<class T, class E>
bool Trie<T, E>::empty() const {
    return false;
}

template<class T, class E>
void Trie<T, E>::erase(const Trie::key_type &value) {

}

template<class T, class E>
void Trie<T, E>::clear() {

}
