//
//  Team: Melanie Famao, Christopher Weber
//

#include <map>
#include <string>
#include <stack>
#include "iostream"
#include <cstring>
#include "AbstractNode2.h"

#ifndef PRAKTIKUM_2_TRIE2_H
#define PRAKTIKUM_2_TRIE2_H


const static char TERMINAL_ZEICHEN = '\0';

template<class T, class E=char>
class Trie2 {
public:
    class InnerNode2;

    class LeafNode2;

    class PostorderTreeTraversal2;

    typedef std::basic_string<E> key_type; // string=basic_string<char>
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;

    //--------------------- Nodes ----------------------------------------------------------
    //--------------------------------------------------------------------------------------------
    class InnerNode2 : public AbstractNode2<T, E> {
    public:
        typedef std::map<E, AbstractNode2<T, E> *> map;
        typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;

        map nextChilds;

        InnerNode2() = default;

        InnerNode2(bool isLeaf) : nextChilds(), AbstractNode2<T, E>(isLeaf) {
        };

        /*   Methode ist Ursache der Segmentation-Fault -> deswegen nicht benutzt, bzw auskommentiert.
        map getAllNextChilds() {
            return nextChilds;
        } */

        void setnewChild(AbstractNode2<T, E> *newChild, E key) {
            if (newChild == nullptr) {
                std::cout << "nullptr help";
            } else {
                nextChilds[key] = newChild;
            }
        }

        /**
         * This method takes the char from the key at the location of size and inserts it at the current Node as Child.
         * Sie ist gedacht, bei 0 anzufangen.
         * (Wurde erstellt, als die Uhrsache des Segmentation-Faults noch nicht bekannt war.)
         * @param value the key, value pair from insert.
         * @param size counter of the recursion
         */
        void addnewBranch(value_type value, int size) {
            if (size >= value.first.size()) {
                LeafNode2 *nextLeaf = new LeafNode2(value.second, true);
                setnewChild(nextLeaf, TERMINAL_ZEICHEN);
            } else {
                char currentChar = value.first.at(size);
                typename map::iterator nextChildsItr = nextChilds.find(value.first.at(size));
                InnerNode2 *nextNode;
                if (nextChilds.empty() || nextChildsItr == nextChilds.end()) {
                    nextNode = new InnerNode2(false);
                    setnewChild(nextNode, value.first.at(size));
                } else {
                    nextNode = (InnerNode2 *) (nextChildsItr.operator*().second);
                }
                (*nextNode).addnewBranch(value, (size + 1));
            }

        }

        /**
         * Searches for the char, from key at position depth, in the childs from the current node. If it was found, it gets pushed in the stack of the iterator.
         * if it was not found, the stack gets emptied and the iterator is the end-iterator.
         *( Wurde erstellt, als die Uhrsache des Segmentation-Faults noch nicht bekannt war.)
         * @param testElement key to find
         * @param depth counter of the recursion
         * @param iterator iterator for the path from key.
         */
        void helperFind(const Trie2::key_type &testElement, int depth, PostorderTreeTraversal2 &iterator) {
            typename map::iterator nextChildsItr;
            //check the depth
            if (depth >= testElement.size()) {
                nextChildsItr = nextChilds.find(TERMINAL_ZEICHEN);
            } else {
                nextChildsItr = nextChilds.find(testElement.at(depth));
            }
            //check the Iterator
            if (nextChildsItr == nextChilds.end()) {
                while (!iterator.current.empty()) {
                    iterator.current.pop();
                }
                return;
            } else {
                std::pair<mapIterator, mapIterator> newPair = std::make_pair(nextChildsItr, nextChilds.end());
                iterator.current.push(newPair);
            }
            //check if another operation is needed
            if (depth < testElement.size()) {
                InnerNode2 *nextNode = (InnerNode2 *) (nextChildsItr.operator*().second);
                (*nextNode).helperFind(testElement, (depth + 1), iterator);
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

/**
 * iterator, that iterates between the leafs of trie.
 */
    class PostorderTreeTraversal2 {
    public:
        typedef AbstractNode2<T, E> node;
        typedef PostorderTreeTraversal2 iterator;
        typedef typename std::map<E, node *>::iterator mapIterator;

        typedef std::stack<std::pair<mapIterator, mapIterator>> stack;

        InnerNode2 *root;
        stack current;

        explicit PostorderTreeTraversal2(InnerNode2 *root) : root(root) {};

        PostorderTreeTraversal2(const PostorderTreeTraversal2 &newIterator) {
            root = newIterator.root;
            current = newIterator.current;
        }

        /**
         * Helper-method to get the first childs of the root in the stack.
         * And then going to the first leaf.
         * There for easier end() in Trie.
         */
        void initializeStack() {
            std::pair<mapIterator, mapIterator> newPair = std::make_pair((*root).nextChilds.begin(),
                                                                         (*root).nextChilds.end());
            current.push(newPair);
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
            mapIterator currentElementItr = currentPair.first;

            if (currentElementItr.operator*().second->isLeaf) {
                //++currentElementItr;
                while (++currentElementItr == currentPair.second) {
                    current.pop();
                    if (current.empty()) {
                        return *this;
                    }
                    currentPair = current.top();
                    currentElementItr = currentPair.first;
                }
                mapIterator savedEnd = current.top().second;
                currentPair = std::make_pair(currentElementItr, savedEnd);
                current.pop();
                current.push(currentPair);
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

        /**
         * Helper Method to get to the leftmost side.
         */
        void slideLeft() {
            std::pair<mapIterator, mapIterator> currentPair = current.top();
            AbstractNode2<T, E> *firstElement = currentPair.first.operator*().second;
            int stop;
            while (!(firstElement)->isLeaf) {
                InnerNode2 *currentElement = (InnerNode2 *) firstElement;

                mapIterator currentElItr = (*currentElement).nextChilds.begin();
                if (currentElItr != (*currentElement).nextChilds.end()) {
                    std::pair<mapIterator, mapIterator> newPair = std::make_pair(currentElItr,
                                                                                 (*currentElement).nextChilds.end());
                    current.push(newPair);
                }
                currentPair = current.top();
                firstElement = currentPair.first.operator*().second;
            }
        }
    };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    typedef PostorderTreeTraversal2 iterator;
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;

    InnerNode2 *startRoot;

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

    void printTree();

};

/**
 * @return the first leaf in trie.
 */
template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::begin() {
    Trie2::iterator tmpItr = Trie2::PostorderTreeTraversal2(startRoot);
    tmpItr.initializeStack();
    return tmpItr;
}

/**
 * @return the end-iterator of trie.
 */
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
typename Trie2<T, E>::iterator Trie2<T, E>::insert(const Trie2::value_type &value) {
    (*startRoot).addnewBranch(value, 0);
    Trie2<T, E>::PostorderTreeTraversal2
            elementItr = find(value.first);
    return elementItr;

}

/** Searches the Tree for a key and gives back the iterator to the value of the key.
 *  The end iterator will be returned, if no matching key was found.
 * @param testElement The key to search for.
 * @return Iterator pointing to the value of the key.
 */
template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::find(const Trie2::key_type &testElement) {
    Trie2<T, E>::PostorderTreeTraversal2
            elementIterator(startRoot);
    (*startRoot).helperFind(testElement, 0, elementIterator);

    return elementIterator;
}

/** If the end Iterator is the output, then there was no key in the trie, that was greater then testElement.
 * Else gives an iterator to the next greater leaf.
 *
 * @return iterator with the path to the next leaf, whose key is greater than testElement.
 */
// first element > testElement
template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::upper_bound(const Trie2::key_type &testElement) {
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;
    //1. Fall: Trie is empty
    if (Trie2<T, E>::empty()) {
        std::cout << "The trie is empty";
        return Trie2<T, E>::end();
    }
    //2. Fall: testElement is in Trie
    Trie2<T, E>::PostorderTreeTraversal2 tmpItr(startRoot);
    Trie2<T, E>::PostorderTreeTraversal2 elementItr = Trie2<T, E>::find(testElement);
    if (elementItr != Trie2<T, E>::end()) {
        ++elementItr;
        return elementItr;
    }
    //3. Fall: testElement is not in Trie
    InnerNode2 *currentNode = startRoot;
    E characterFromNode;
    mapIterator nodeItr = currentNode->nextChilds.begin();
    int depth = 0;
    bool wasNoGreaterCharFound = false;
    bool isFinished = false;

    while (depth < testElement.size()) {
        while (nodeItr != currentNode->nextChilds.end()) {
            characterFromNode = nodeItr.operator*().first;

            if (characterFromNode == testElement.at(depth)) { //same Character
                std::pair<mapIterator, mapIterator> newPair = std::make_pair(nodeItr, currentNode->nextChilds.end());
                tmpItr.current.push(newPair);
                wasNoGreaterCharFound = false;
                break;
                //Character from Node is greater than Char in testElement. Greater Word found.
            } else if (characterFromNode > testElement.at(depth)) {
                std::pair<mapIterator, mapIterator> newPair = std::make_pair(nodeItr, currentNode->nextChilds.end());
                tmpItr.current.push(newPair);
                wasNoGreaterCharFound = false;
                isFinished = true;
                break;
            } else { //character from Node is less than Char in testElement.
                wasNoGreaterCharFound = true;
            }
            ++nodeItr;
        }

        if (isFinished) {
            break;
        } else if (wasNoGreaterCharFound) {
            if (tmpItr.current.empty()) { //just to make sure.
                return Trie2<T, E>::end();
            }
            mapIterator rememberNodeItr = tmpItr.current.top().first;
            mapIterator rememberNodeItrEnd = tmpItr.current.top().second;
            tmpItr.current.pop();
            wasNoGreaterCharFound = false;

            //the saved node/child was already checked -> we need to check the char from the neighboring child.
            //when no neighbor is found, we save the status of the previous row and check again. until neighbor found or stack empty.
            while (++rememberNodeItr == rememberNodeItrEnd) {
                if (tmpItr.current.empty()) {
                    break;
                }
                rememberNodeItr = tmpItr.current.top().first;
                rememberNodeItrEnd = tmpItr.current.top().second;
                tmpItr.current.pop();
                --depth;
            }
            //check status of stack and nodes again, because it is unclear which condition in while-loop was met.
            if (tmpItr.current.empty()) {
                //Check if we had unvisited childs in the root of trie.
                if (rememberNodeItr != rememberNodeItrEnd) {
                    currentNode = startRoot;
                } else {
                    return Trie2<T, E>::end();
                }
            } else {
                std::pair<mapIterator, mapIterator> lastPair = tmpItr.current.top();
                currentNode = (InnerNode2 *) lastPair.first.operator*().second;
            }
            nodeItr = rememberNodeItr;
            --depth;
        } else {
            currentNode = (InnerNode2 *) nodeItr.operator*().second;
            nodeItr = currentNode->nextChilds.begin();
            ++depth;
        }
    }

    elementItr = PostorderTreeTraversal2(tmpItr);
    elementItr.slideLeft();
    return elementItr;
}

/** If the end Iterator is the output, then there was no key in the trie, that was greater then or equal testElement.
 * Else gives an iterator to the next greater/equal leaf.
 * Uses find to check, if there is an equal element in the trie.
 * if none found, upper_bound searches for an greater element than testElement.
 * @return terator with the path to the next leaf, whose key is greater than or equal testElement.
 */
// first element >= testElement
template<class T, class E>
typename Trie2<T, E>::iterator Trie2<T, E>::lower_bound(const Trie2::key_type &testElement) {
    PostorderTreeTraversal2 elementItr = find(testElement);
    if (elementItr != end()) {
        return elementItr;
    } else {
        elementItr = upper_bound(testElement);
        return elementItr;
    }
}

/**
 * check if the Trie is empty.
 * @return If the Trie is empty.
 */
template<class T, class E>
bool Trie2<T, E>::empty() const {
    return startRoot->nextChilds.empty();
}

/**
 * erases the value, if it's in the trie.
 * @param value value to erase
 */
template<class T, class E>
void Trie2<T, E>::erase(const Trie2::key_type &value) {
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;
    Trie2<T, E>::PostorderTreeTraversal2 deleteIterator = Trie2<T, E>::find(value);
    bool canDelete = true;
    int indexToDelete = value.size();

    if (deleteIterator != Trie2<T, E>::end()) {
        deleteIterator.current.pop();
        while (!deleteIterator.current.empty()) {
            std::pair<mapIterator, mapIterator> currPair = deleteIterator.current.top();
            mapIterator currMapItr = currPair.first;
            InnerNode2 *currentNode = (InnerNode2 *) currMapItr.operator*().second;
            bool tmpCanDelete = currentNode->nextChilds.size() < 2;

            if (canDelete) {
                if (indexToDelete >= value.size()) {
                    //leaf needs to be deleted
                    AbstractNode2<T, E> *toDelete = currentNode;//next child node first erase map then node
                    currentNode->nextChilds.erase(TERMINAL_ZEICHEN);;
                    delete ((*toDelete));
                    --indexToDelete;
                    deleteIterator.current.pop();
                    //currPair = deleteIterator.current.top();
                    //currentNode = (InnerNode2 *) currPair.first.operator*().second;
                } else if (indexToDelete >= 0) {
                    //rest needs to be deleted
                    AbstractNode2<T, E> *toDelete = currentNode;
                    currentNode->nextChilds.erase(value.at(indexToDelete));
                    delete ((*toDelete));
                    --indexToDelete;
                    deleteIterator.current.pop();
                }

                canDelete = tmpCanDelete;
            } else {
                break;
            }
        }
    }
}

template<class T, class E>
void Trie2<T, E>::printTree() {
    typedef typename std::map<E, AbstractNode2<T, E> *>::iterator mapIterator;
    int depth = 0;
    std::pair<mapIterator, mapIterator> newPair;
    std::stack<std::pair<mapIterator, mapIterator>> whereAmI;
    newPair = std::make_pair(startRoot->nextChilds.begin(), startRoot->nextChilds.end());
    whereAmI.push(newPair);

    mapIterator mapItr = whereAmI.top().first;
    AbstractNode2<T, E> *currentNode = mapItr.operator*().second;


}


#endif //PRAKTIKUM_2_TRIE2_H
