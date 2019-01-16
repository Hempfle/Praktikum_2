//
// Created by Mel on 13.01.2019.
//

#include "Main.h"
#include "Trie2.h"
#include "iostream"

bool testTrieInsertAndFind() {
    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt01 = testTrie.insert(std::make_pair("Katze", "cat"));
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt02 = testTrie.insert(std::make_pair("nein", "no"));
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt03 = testTrie.insert(
            std::make_pair("Katzenbaum", "cattree"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testIt1 = testTrie.find("Katze");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt2 = testTrie.find("nein");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt3 = testTrie.find("Katzenbaum");
    Trie2<std::string, char>::PostorderTreeTraversal2 testFindEnd = testTrie.find("neid");


    std::string firstObj = (*testIt1);
    std::string secondObj = (*testIt2);
    std::string thirdObj = (*testIt3);

    int testInt = firstObj.compare("cat");
    int testInt2 = secondObj.compare("no");
    int testInt3 = thirdObj.compare("cattree");

    return (testInt) == 0 && testInt2 == 0 && testIt01 == testIt1 && testIt02 == testIt2 && testIt03 == testIt3 &&
           testInt3 == 0 && testFindEnd == testTrie.end();
}

bool testBeginAndEnd() {
    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt01 = testTrie.insert(std::make_pair("nein", "no"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testEnd = Trie2<std::string, char>::PostorderTreeTraversal2(
            testTrie.startRoot);

    return testTrie.begin() == testIt01 && testTrie.end() == testEnd;

}

bool testUpperBound() {
    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    testTrie.insert(std::make_pair("anker", "anker"));
    testTrie.insert(std::make_pair("ball", "ball"));
    testTrie.insert(std::make_pair("bube", "boy"));
    testTrie.insert(std::make_pair("bursche", "boy"));
    testTrie.insert(std::make_pair("suppe", "soup"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testIt01 = testTrie.upper_bound("butter");

    Trie2<std::string, char> testTrie2 = Trie2<std::string, char>();
    testTrie2.insert(std::make_pair("Dora", "Hallo"));
    testTrie2.insert(std::make_pair("Ha", "Hilfe"));
    testTrie2.insert(std::make_pair("H", "Junge"));
    testTrie2.insert(std::make_pair("Hilflos", "Hilfe"));
    testTrie2.insert(std::make_pair("Xaver", "Ende"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testIt20 = testTrie2.upper_bound("Hut");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt21 = testTrie2.upper_bound("Baum");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt22 = testTrie2.upper_bound("Hilfloz");

    Trie2<std::string, char> testTrie3 = Trie2<std::string, char>();
    testTrie3.insert(std::make_pair("Hallo", "Dora"));
    testTrie3.insert(std::make_pair("Hilfe", "Ha"));
    testTrie3.insert(std::make_pair("Junge", "H"));
    testTrie3.insert(std::make_pair("Ende", "Xaver"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testIt30 = testTrie3.upper_bound("Junge");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt31 = testTrie3.upper_bound("Hilt");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt32 = testTrie3.upper_bound("Hallo");


    return (*testIt01) == "soup" && (*testIt20) == "Ende" && testIt30 == testTrie3.end() && (*testIt31) == "H" &&
           (*testIt21) == "Hallo" && (*testIt22) == "Ende" && (*testIt32) == "Ha";
}

bool testIncrementInterator() {
    bool allPassed = true;

    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    testTrie.insert(std::make_pair("anker", "anker"));
    testTrie.insert(std::make_pair("ball", "ball"));
    testTrie.insert(std::make_pair("bube", "boy"));
    testTrie.insert(std::make_pair("bursche", "sure"));
    testTrie.insert(std::make_pair("suppe", "soup"));

    Trie2<std::string, char>::PostorderTreeTraversal2 testIt01 = testTrie.begin();
    allPassed = (*testIt01) == "anker";
    ++testIt01;
    allPassed = (*testIt01) == "ball";
    ++testIt01;
    allPassed = (*testIt01) == "boy";
    ++testIt01;
    allPassed = (*testIt01) == "sure";
    ++testIt01;
    allPassed = (*testIt01) == "soup";
    ++testIt01;
    allPassed = testIt01 == testTrie.end();

    return allPassed;
}

bool testErase() {
    bool allPassed = true;

    Trie2<std::string, char> testTrie = Trie2<std::string, char>();
    testTrie.insert(std::make_pair("anker", "anker"));
    testTrie.insert(std::make_pair("ball", "ball"));
    testTrie.insert(std::make_pair("bube", "boy"));

    Trie2<std::string, char> testTrie1 = Trie2<std::string, char>();
    testTrie1.insert(std::make_pair("anker", "anker"));
    testTrie1.insert(std::make_pair("ball", "ball"));
    testTrie1.insert(std::make_pair("bube", "boy"));

    Trie2<std::string, char> testTrie2 = Trie2<std::string, char>();
    testTrie2.insert(std::make_pair("anker", "anker"));
    testTrie2.insert(std::make_pair("ball", "ball"));
    testTrie2.insert(std::make_pair("bube", "boy"));
}

//------------ start here ----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

int main() {
//TestMethods for Trie
    if (testTrieInsertAndFind()) {
        std::cout << "Test Insert() and Find() passed" << "\n";
    } else {
        std::cout << "Test Insert() and Find() failed." << "\n";
    }
    if (testBeginAndEnd()) {
        std::cout << "Test Begin() and End() passed" << "\n";
    } else {
        std::cout << "Test Begin() and End() failed." << "\n";
    }
    if (testUpperBound()) {
        std::cout << "Test Upper_Bound() passed" << "\n";
    } else {
        std::cout << "Test Upper_Bound() failed." << "\n";
    }
    if (testIncrementInterator()) {
        std::cout << "Test testIncrementInterator() passed" << "\n";
    } else {
        std::cout << "Test testIncrementInterator() failed." << "\n";
    }

    //TestMethods for Iterator


    return 0;
}