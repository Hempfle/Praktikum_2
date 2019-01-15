//
// Created by Mel on 13.01.2019.
//

#include "Main.h"
#include "Trie2.h"
#include "iostream"

bool testTrieInsertAndFind() {
    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    testTrie.insert(std::make_pair("nein", "no"));
    testTrie.insert(std::make_pair("Katze", "cat"));
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt1 = testTrie.find("Katze");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt2 = testTrie.find("nein");

    return (*testIt1).compare("cat") == 0 && (*testIt2).compare("no");
}

int main() {

    if (testTrieInsertAndFind()) {
        std::cout << "Test true";
    } else {
        std::cout << "Test failed." ;
    }



    //TestMethods for Iterator


    //TestMethods for Trie


    return 0;
}