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

template<class T, class E=char>
class Trie {
public:
    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::map<const key_type, T> value_type;
    typedef T mapped_type;

    bool empty() const;

    void erase(const key_type &value);

    void clear(); // erase all


    class innerNode : AbstractNode<T> {
//jeder knoten hat eine map, bsp. e zeigt auf pointer


    };

    class leafNode : AbstractNode<T> {

    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class TrieIterator {

    };
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    typedef TrieIterator iterator;

    iterator insert(const value_type &value);

    iterator lower_bound(const key_type &testElement); // first element >= testElement
    iterator upper_bound(const key_type &testElement); // first element > testElement
    iterator find(const key_type &testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    class postorderTreeTraversal {
    public:
        typedef AbstractNode<T> node;
        typedef postorderTreeTraversal iterator;
        typedef std::stack<std::map<E, node>::iterator> stack;

        node* root;
        stack current;


        postorderTreeTraversal(node* root) : root(root), current(root->nextNodes.begin()) {};

        postorderTreeTraversal(const iterator &itr) : current(itr.current) {}

        iterator &operator=(const iterator &itr) {
            root = itr.root;
            current = itr.current;
            return *this;
        }

        bool operator==(const iterator &itr) {
            return current == itr.current && root == itr.root;
        }

        bool operator!=(const iterator &itr) { return !operator==(itr); }

        T &operator*() { return current.top(); }

        iterator &operator++(); // prefix
        iterator operator++(int) // postfix
        {
            iterator clone(*this);
            operator++();
            return clone;
        }


    };

};