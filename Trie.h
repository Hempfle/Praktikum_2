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

class postorderTreeTraversal;

template<class T, class E=char>
class Trie {
public:

    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::map<const key_type, T> value_type;
    typedef T mapped_type;

    //------------------------  Node classes -------------------------------------------------------------------------------------------------
    class innerNode : AbstractNode<T> {
    public:
        innerNode() : AbstractNode<innerNode, E>() {};

        explicit innerNode(leafNode *firstChild, E key) : AbstractNode<innerNode, E>() {
            setNewChild(key, firstChild);
        };

        explicit innerNode(innerNode *firstChild, E key) : AbstractNode<innerNode, E>() {
            setNewChild(key, firstChild);
        };

    };

    class leafNode : AbstractNode<T> {
    public:
        key_type pathToValue;

        leafNode() = default;

        leafNode(mapped_type valueLeaf, key_type pathToValue) : AbstractNode<key_type, E>(valueLeaf),
                                                                pathToValue(pathToValue) {};

        virtual void setNewChild(E key, T *next) {} //Leaf Nodes never get childs.

    };

//---------------------------------------------------------------------------------------------------------------------------

    //~~~~~~~~~~~~~~~~~~  Iterator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    class postorderTreeTraversal {
    public:
        typedef AbstractNode<T> node;
        typedef postorderTreeTraversal iterator;
        typedef typename std::map<E, node>::iterator mapIterator;

        typedef std::stack<std::pair<mapIterator, mapIterator>> stack;

        node *root;
        stack current;

        postorderTreeTraversal(node *root) : root(root), current() {
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

        T &operator*() { //todo: if-Abfrage nötig?
            std::pair<mapIterator, mapIterator> tmp = current.top();

            if (tmp.first != tmp.second) {
                return *tmp.first;
            }
        }

        iterator &operator++() { // prefix
            std::pair<mapIterator, mapIterator> currentPair = current.top();

            if (!current.empty() && currentPair.first != currentPair.second) {
                slideLeft();
                return *this;
            } else {
                while (!current.empty() && currentPair.first == currentPair.second) {
                    current.pop();
                    std::pair<mapIterator, mapIterator> curPair = current.top();
                    if (curPair.first != curPair.second) {
                        ++curPair.first;
                    }
                }
                if (current.empty()) {
                    return root->getAllNextNodes().end();
                }
                slideLeft();
                return *this;
            }

        }

        iterator operator++(int) { // postfix
            iterator clone(*this);
            operator++();
            return clone;
        }

        void slideLeft() {
            std::pair<mapIterator, mapIterator> currentPair = current.top();

            while (currentPair.first != currentPair.second) {
                node currentElement = *currentPair.first;
                current.push(std::make_pair(currentElement.getAllNextNodes().begin(),
                                            currentElement.getAllNextNodes().end()));

                currentPair = current.top();
            }
        }

    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    typedef postorderTreeTraversal iterator;

    const char TERMINAL_ZEICHEN = '\0';

    innerNode *startRoot;

    Trie() = default;

    bool empty() const;

    void erase(const key_type &value);

    void clear(); // erase all

    iterator insert(const value_type &value);

    iterator lower_bound(const key_type &testElement); // first element >= testElement
    iterator upper_bound(const key_type &testElement); // first element > testElement
    iterator find(const key_type &testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();

};

template<class T, class E>
bool Trie<T, E>::empty() const {
    return startRoot->getAllNextNodes().empty();
}

template<class T, class E>
void Trie<T, E>::erase(const Trie::key_type &value) {

}

template<class T, class E>
void Trie<T, E>::clear() {
    startRoot->getAllNextNodes().clear();
}

/**
 * Inserts the element into the trie. Gives back the iterator pointing to the inserted element.
 * @tparam T
 * @tparam E
 * @param value The value to insert.
 * @return iterator pointing to the inserted element.
 */
template<class T, class E>
postorderTreeTraversal Trie<T, E>::insert(const Trie::value_type &value) {
    return Trie::iterator(nullptr);
}

/**
 *
 * @tparam T
 * @tparam E
 * @param testElement
 * @return
 */
template<class T, class E>
postorderTreeTraversal Trie<T, E>::lower_bound(const Trie::key_type &testElement) {
    return Trie::iterator(nullptr);
}

/**
 *
 * @tparam T
 * @tparam E
 * @param testElement
 * @return
 */
template<class T, class E>
postorderTreeTraversal Trie<T, E>::upper_bound(const Trie::key_type &testElement) {
    return Trie::iterator(nullptr);
}

/**
 * searches the trie for an element. Gives back the iterator pointing to the searched element, or the end-it ot trie
 * @tparam T
 * @tparam E
 * @param testElement The element to find.
 * @return Iterator pointing to the searched element, or the end-iterator of the trie.
 */
template<class T, class E>
postorderTreeTraversal Trie<T, E>::find(const Trie::key_type &testElement) {
    return Trie::iterator(nullptr);
}

/**
 * Get an iterator that is pointing to the first child of the root.
 * @tparam T
 * @tparam E
 * @return begin-iterator.
 */
template<class T, class E> //todo same as end.
postorderTreeTraversal Trie<T, E>::begin() {
    postorderTreeTraversal it = postorderTreeTraversal(*startRoot);
    ++it;
    return it;
}

/**
 * Get an iterator that is pointing to the end-it of the root.
 * @tparam T
 * @tparam E
 * @return end-iterator.
 */
template<class T, class E> //todo: end iterator darf auch normaler iterator sein?
postorderTreeTraversal Trie<T, E>::end() {
    postorderTreeTraversal it = postorderTreeTraversal(*startRoot);
    //return startRoot->getAllNextNodes().end();


}
