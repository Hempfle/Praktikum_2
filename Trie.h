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

class innerNode;

class leafNode;

class postorderTreeTraversal;

template<class T, class E=char>
class Trie {
public:

    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;

    //------------------------  Node classes -----------------------------------------------------
    //--------------------------------------------------------------------------------------------
    class InnerNode : public AbstractNode<T, E> {
    public:
        InnerNode() : AbstractNode<T, E>() {};
    };

    class LeafNode : public AbstractNode<T, E> {
    public:
        LeafNode() = default;

        LeafNode(mapped_type valueLeaf) : AbstractNode<mapped_type, E>(valueLeaf) {};

        virtual void setNewChild(E key, AbstractNode<T, E> *next) {} //Leaf Nodes never get childs.

    };

    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------

    //~~~~~~~~~~~~~~~~~~  Iterator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    class PostorderTreeTraversal {
    public:
        typedef AbstractNode<T> node;
        typedef PostorderTreeTraversal iterator;
        typedef typename std::map<E, node*>::iterator mapIterator;

        typedef std::stack<std::pair<mapIterator, mapIterator>> stack;

        InnerNode *root;
        stack current;

        explicit PostorderTreeTraversal(InnerNode *root) : root(root) {};

        void initializeStack() {
            current.push(std::make_pair(root->nextNodes.begin(), root->nextNodes.end()));
        }

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
                return tmp.first.operator*().second.getValue();
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
            mapIterator firstElement = currentPair.first;

            while (firstElement.operator*().first != Trie::TERMINAL_ZEICHEN) {
                node currentElement = firstElement.operator*().second;
                current.push(std::make_pair(currentElement.getAllNextNodes().begin(),
                                            currentElement.getAllNextNodes().end()));

                currentPair = current.top();
                firstElement = currentPair.first;
            }
        }
    };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    typedef PostorderTreeTraversal iterator;

    const static char TERMINAL_ZEICHEN = '\0';

    InnerNode startRoot;

    Trie() {
        startRoot = InnerNode();
    };

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

/** Erases the key-path from the trie. If the key is not present, then nothing will happen.
 * @param value Key to erase from the trie.
 */
template<class T, class E> //todo: fertig machen
void Trie<T, E>::erase(const Trie::key_type &value) {
    PostorderTreeTraversal isValueThere = Trie<T, E>::find(value);
    if (isValueThere != Trie<T, E>::end()) {



    } else {
        return;
    }

}


template<class T, class E> //todo: wahrscheinlich falsch?...
void Trie<T, E>::clear() {
    startRoot->getAllNextNodes().clear();
}

/**
 * Inserts the element of the map into the trie. Gives back the iterator pointing to the inserted element.
 * @param value The value to insert.
 * @return iterator pointing to the inserted element.
 */
template<class T, class E>
typename Trie<T, E>::iterator Trie<T, E>::insert(const Trie::value_type &value) {
    key_type tmpKeyForInsert = value.first;
    PostorderTreeTraversal elementIterator = Trie::begin();

    InnerNode *currentNode = &startRoot;
    typename std::map<E, T *>::iterator nodeCharacterIt;
    int counterFoundKeyChar = 0;

    for (int i = 0; i < tmpKeyForInsert.size(); ++i) {

        nodeCharacterIt = currentNode->getAllNextNodes().find(tmpKeyForInsert.at(i));
        if (nodeCharacterIt == currentNode->getAllNextNodes().end()) {
            InnerNode nextChild = InnerNode();
            currentNode->setNewChild(tmpKeyForInsert.at(i), &nextChild);

            elementIterator.current.push(std::make_pair(currentNode->getAllNextNodes().find(tmpKeyForInsert.at(i)),
                                                        currentNode->getAllNextNodes().end()));

            currentNode = &nextChild;
        } else {
            elementIterator.current.push(std::make_pair(nodeCharacterIt, currentNode->getAllNextNodes().end()));

            currentNode = nodeCharacterIt.operator*().second;
            ++counterFoundKeyChar;
        }
    }
    //element already in trie
    if (counterFoundKeyChar == tmpKeyForInsert.size()) {
        elementIterator.current.push(std::make_pair(currentNode->getAllNextNodes().find(Trie::TERMINAL_ZEICHEN),
                                                    currentNode->getAllNextNodes().end()));
        return elementIterator;
    }

    LeafNode newLeaf = LeafNode(value.second);
    currentNode->setNewChild(Trie::TERMINAL_ZEICHEN, &newLeaf);
}

/**
 *
 * @param testElement the Element to adjust the search for.
 * @return
 */
template<class T, class E> //todo: fertig machen
typename Trie<T, E>::iterator Trie<T, E>::lower_bound(const Trie::key_type &testElement) {


}

/**
 *
 * @param testElement the Element to adjust the search for.
 * @return
 */
template<class T, class E> //todo fertig machen
typename Trie<T, E>::iterator Trie<T, E>::upper_bound(const Trie::key_type &testElement) {


}

/**
 * searches the trie for an element. Gives back the iterator pointing to the searched element, or the end-it of trie
 * @param testElement The element to find.
 * @return Iterator pointing to the searched element, or the end-iterator of the trie.
 */
template<class T, class E>
typename Trie<T, E>::iterator Trie<T, E>::find(const Trie::key_type &testElement) {
    PostorderTreeTraversal elementIterator = PostorderTreeTraversal(startRoot);
    InnerNode *currentNode = &startRoot;
    typename std::map<E, T *>::iterator nodeCharacterIt;
    int testElementSize = testElement.size();

    for (int i = 0; i <= testElementSize; ++i) {
        if (i >= testElementSize) {
            nodeCharacterIt = currentNode->getAllNextNodes().find(Trie::TERMINAL_ZEICHEN);
            elementIterator.current.push(std::make_pair(nodeCharacterIt, currentNode->getAllNextNodes().end()));
        } else {
            nodeCharacterIt = currentNode->getAllNextNodes().find(testElement.at(i));
            if (nodeCharacterIt != currentNode->getAllNextNodes().end()) {
                elementIterator.current.push(std::make_pair(nodeCharacterIt, currentNode->getAllNextNodes().end()));
                currentNode = nodeCharacterIt.operator*().second;
            } else {
                return Trie<T, E>::end();
            }
        }
    }
    return elementIterator;

}

/**
 * Get an iterator that is pointing to the first leaf of the root.
 * @return begin-iterator, the first leaf.
 */
template<class T, class E>
typename Trie<T, E>::iterator Trie<T, E>::begin() {
    PostorderTreeTraversal it = PostorderTreeTraversal(startRoot);
    it.initializeStack();
    ++it;
    return it;
}

/**
 * Get an iterator that is pointing to the end-it of the root.
 * End iterator means the stack is empty.
 * @return end-iterator.
 */
template<class T, class E>
typename Trie<T, E>::iterator Trie<T, E>::end() {
    PostorderTreeTraversal it = PostorderTreeTraversal(startRoot);
    return it;
}


