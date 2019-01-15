//
// Created by Mel on 13.01.2019.
//

#include <map>
#include <string>
#include <stack>
#include "iostream"
#include "AbstractNode2.h"
#include <memory>

#ifndef PRAKTIKUM_2_TRIE2_H
#define PRAKTIKUM_2_TRIE2_H

class innerNode2;

class leafNode2;

class postorderTreeTraversal2;

const static char TERMINAL_ZEICHEN = '\0';

template<class T, class E=char>
class Trie2 {

public:

    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;

    //------------------------  Node classes -----------------------------------------------------
    //--------------------------------------------------------------------------------------------
    class InnerNode2 : public AbstractNode2<T, E> {
    public:
        typedef std::map<E, AbstractNode2<T, E> *> map;
        map nextChilds;

        InnerNode2() = default;

        InnerNode2(bool isLeaf) : nextChilds(), AbstractNode2<T, E>(isLeaf) {
        };

        map getAllNextChilds() {
            return nextChilds;
        }

        void setnewChild(AbstractNode2<T, E> *newChild, E key) {
            if (newChild == nullptr) {
                std::cout << "nullptr help";
            } else {
                nextChilds[key] = newChild;
            }
        }

        void addnewBranch(value_type value, int size) {
            if (size >= value.first.size()) {
                LeafNode2* nextLeaf = new LeafNode2(value.second, true);
                setnewChild(nextLeaf, TERMINAL_ZEICHEN);
            } else {
                char currentChar = value.first.at(size);
                typename std::map<E, AbstractNode2<T, E> *>::iterator nextChildsItr = nextChilds.find(value.first.at(size));
                InnerNode2* nextNode;
                if (nextChilds.empty() || nextChildsItr == nextChilds.end()) {
                    nextNode = new InnerNode2(false);
                    setnewChild(nextNode, value.first.at(size));
                } else {
                    nextNode = (InnerNode2 *) (nextChildsItr.operator*().second);
                }
                (*nextNode).addnewBranch(value, (size + 1));
            }

        }

    };

    class LeafNode2 : public AbstractNode2<T, E> {
    public:
        T value;

        LeafNode2() = default;
        LeafNode2(T leafValue, bool isLeaf) : value(leafValue), AbstractNode2<T, E>(isLeaf) {};

        T getValue() {
            return value;
        }

        T &operator*() {
            return value;
        }
    };

    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------

    //~~~~~~~~~~~~~~~~~~  Iterator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    class PostorderTreeTraversal2 {
    public:
        typedef AbstractNode2<T, E> node;
        typedef PostorderTreeTraversal2 iterator;
        typedef typename std::map<E, node *>::iterator mapIterator;

        typedef std::stack<std::pair<mapIterator, mapIterator>> stack;

        InnerNode2 *root;
        stack current;

        explicit PostorderTreeTraversal2(InnerNode2 *root) : root(root) {};

        void initializeStack() {
            current.push(std::make_pair(root->getAllNextChilds().begin(), root->getAllNextChilds().end()));
            slideLeft();
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

        T operator*() {
            std::pair<mapIterator, mapIterator> tmp = current.top();
            LeafNode2 *node = (LeafNode2 *) tmp.first.operator*().second;
            return node->getValue();
        }

        iterator &operator++() { // prefix
            std::pair<mapIterator, mapIterator> currentPair = current.top();
            mapIterator *currentElementItr = &currentPair.first;

            if (currentElementItr->operator*().second->isLeaf) {
                ++(*currentElementItr);
                while (currentElementItr == currentPair.second) {
                    current.pop();
                    if (current.empty()) {
                        return *this;
                    }
                    currentPair = current.top();
                    currentElementItr = &currentPair.first;
                    ++(*currentElementItr);
                }
                slideLeft();
                return *this;
            } else {
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

            while (!firstElement.operator*().second->isLeaf) {
                InnerNode2 currentElement = firstElement.operator*().second;

                mapIterator currentElItr = currentElement.getAllNextChilds().begin();
                if (currentElItr != currentElement.getAllNextChilds().end()) {
                    current.push(std::make_pair(currentElItr,
                                                currentElement.getAllNextChilds().end()));

                }

                currentPair = current.top();
                firstElement = currentPair.first;
            }
        }
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    typedef PostorderTreeTraversal2 iterator;
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;

    InnerNode2* startRoot;

    Trie2() {
        startRoot = new InnerNode2(false);
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

    mapIterator helperFind(key_type key, int depth);

    void printTree();

};

template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::begin() {
    Trie2::iterator tmpItr = Trie2::PostorderTreeTraversal2(startRoot);
    tmpItr.initializeStack();
    return tmpItr;
}

template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::end() {
    Trie2::iterator tmpItr = Trie2::PostorderTreeTraversal2(startRoot);
    return tmpItr;
}

/**
 * Inserts the element of the map into the trie. Gives back the iterator pointing to the inserted element.
 * If a key is already used, it will be overwritten with the new value.
 * @param value The value to insert.
 * @return iterator pointing to the inserted element.
 */
template<class T, class E>
//todo: unterschied * und ->
typename Trie2<T, E>::iterator Trie2<T, E>::insert(const Trie2::value_type &value) {
    (*startRoot).addnewBranch(value, 0);
   PostorderTreeTraversal2 elementItr = find(value.first);
    return elementItr;

 /*
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;

    key_type keyForInsert = value.first;
    PostorderTreeTraversal2 elementIterator = PostorderTreeTraversal2(&startRoot);

    InnerNode2 *currentNode = &startRoot;
    //typename std::map<E, AbstractNode2<T, E> *>::iterator outerItr;
    //insert the chars from key in trie
    for (int i = 0; i < keyForInsert.size(); ++i) {
        std::cout << "i = " << i << "\n";
        typename std::map<E, AbstractNode2<T, E> *>::iterator converseItr = currentNode->getAllNextChilds().find(
                keyForInsert.at(i));
        bool testMap = currentNode->getAllNextChilds().empty();
        if (currentNode->getAllNextChilds().empty() || converseItr == currentNode->getAllNextChilds().end()) {
            InnerNode2 nextChild = new InnerNode2(false);
            (*currentNode).setnewChild(&nextChild, keyForInsert.at(i));

            converseItr = currentNode->getAllNextChilds().find(keyForInsert.at(i));
            std::pair<mapIterator, mapIterator> newPair = std::make_pair(converseItr,
                                                                         currentNode->getAllNextChilds().end());
            elementIterator.current.push(newPair);

            currentNode = &nextChild;
        } else {
            std::pair<mapIterator, mapIterator> newPair = std::make_pair(converseItr,
                                                                         currentNode->getAllNextChilds().end());
            elementIterator.current.push(newPair);

            currentNode = ((InnerNode2 *) converseItr.operator*().second);
        }
    }

    LeafNode2 newLeaf = LeafNode2(value.second, true);
    LeafNode2* newLeafPrt = &newLeaf;
    (*currentNode).setnewChild(newLeafPrt, TERMINAL_ZEICHEN);
    char terminal = TERMINAL_ZEICHEN;
    std::pair<mapIterator, mapIterator> newPair = std::make_pair(currentNode->getAllNextChilds().find(terminal),
                                                                 currentNode->getAllNextChilds().end());
    elementIterator.current.push(newPair);

    return elementIterator; */
}

template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::find(const Trie2::key_type &testElement) {
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;

    Trie2<T, E>::PostorderTreeTraversal2 elementIterator = PostorderTreeTraversal2(startRoot);
    AbstractNode2<T, E> *currentNode = startRoot;
    typename std::map<E, AbstractNode2<T, E> *>::iterator nodeCharacterIt;
    int testElementSize = testElement.size();

    for (int i = 0; i <= testElementSize; ++i) {
        if (i >= testElementSize) {
            nodeCharacterIt = ((InnerNode2 *) currentNode)->getAllNextChilds().find(TERMINAL_ZEICHEN);
            std::pair<mapIterator, mapIterator> newPair = std::make_pair(nodeCharacterIt,
                                                                         ((InnerNode2 *) currentNode)->getAllNextChilds().end());
            elementIterator.current.push(newPair);
        } else {
            nodeCharacterIt = ((InnerNode2 *) currentNode)->getAllNextChilds().find(testElement.at(i));

            if (nodeCharacterIt != ((InnerNode2 *) currentNode)->getAllNextChilds().end()) {
                std::pair<mapIterator, mapIterator> newPair = std::make_pair(nodeCharacterIt,
                                                                             ((InnerNode2 *) currentNode)->getAllNextChilds().end());
                elementIterator.current.push(newPair);

                currentNode = ((*nodeCharacterIt).second);
            } else {
                return Trie2<T, E>::end();
            }
        }
    }
    return elementIterator;
}


#endif //PRAKTIKUM_2_TRIE2_H
