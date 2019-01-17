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

    testTrie.erase("anker");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt00 = testTrie.find("anker");
    allPassed = allPassed ? testIt00 == testTrie.end() : allPassed;
    testIt00 = testTrie.begin();
    allPassed = allPassed ? *testIt00 == "ball" && *(++testIt00) == "boy" : allPassed;

    Trie2<std::string, char> testTrie1 = Trie2<std::string, char>();
    testTrie1.insert(std::make_pair("anker", "anker"));
    testTrie1.insert(std::make_pair("ball", "ball"));
    testTrie1.insert(std::make_pair("bube", "boy"));

    testTrie1.erase("ball");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt10 = testTrie1.find("ball");
    allPassed = allPassed ? testIt10 == testTrie1.end() : allPassed;
    testIt10 = testTrie1.begin();
    allPassed = allPassed ? *testIt10 == "anker" && *(++testIt10) == "boy" : allPassed;

    Trie2<std::string, char> testTrie2 = Trie2<std::string, char>();
    testTrie2.insert(std::make_pair("anker", "anker"));
    testTrie2.insert(std::make_pair("ball", "ball"));
    testTrie2.insert(std::make_pair("bube", "boy"));

    testTrie2.erase("bube");
    Trie2<std::string, char>::PostorderTreeTraversal2 testIt20 = testTrie2.find("bube");
    allPassed = allPassed ? testIt20 == testTrie2.end() : allPassed;
    testIt20 = testTrie2.begin();
    allPassed = allPassed ? *testIt20 == "anker" && *(++testIt20) == "ball" : allPassed;

    return allPassed;
}

//------------ start here ----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;

int main() {

    Trie2<std::string, char> trie = Trie2<std::string, char>();

    int count;
    cout << "Wie viele Eintraege wollem Sie in den Trie hinzufuegen?" << endl;
    cin >> count;

    //fill in trie
    for (int i = 0; i < count; ++i) {
        cout << "Erstelle Eintrag Nummer " << i << endl;
        cout << "Wie lautet der Key " << i << "?" << endl;
        std::basic_string<char> key;
        cin >> key;

        cout << "Wie lautet der Value " << i << "?" << endl;
        std::string value;
        cin >> value;

        std::pair<std::basic_string<char>, std::string> newPair = std::make_pair(key, value);
        trie.insert(newPair);
    }
    cout << "Eintraege wurden hinzugefuegt" << endl;

    //search student
    cout << "Suche einen Eintrag ueber seinen Key!" << endl;
    std::basic_string<char> searchedKey;
    cin >> searchedKey;
    Trie2<std::string, char>::PostorderTreeTraversal2 searchIt = trie.find(searchedKey);
    if (searchIt != trie.end()) {
        cout << "Eintrag mit value: " <<  (*searchIt) << endl;
    } else {
        cout << "Es wurden keine Eintraege mit dem Key " << searchedKey << " gefunden" << endl;
    }

    cout << "Moechten Sie Ihren Trie anzeigen lassen? (false=0/true=1)" << endl;
    bool showTree;
    cin >> showTree;

    if (showTree) {
        trie.printTree();
    }

    cout << endl<< "Moechten Sie einen Eintrag im Trie entfernen? (false=0/true=1)" << endl;
    bool iserase;
    cin >> iserase;

    if (iserase) {
        cout << "Welchen Key wollen sie loeschen? Wenn der Key nicht vorhanden ist passiert nichts." << endl;
        cin >> searchedKey;
        trie.erase(searchedKey);
        cout << "Ihr Baum sieht nun so aus: " << endl;
        trie.printTree();
        cout << endl << "Eingabe beendet." << endl;
    } else {
        cout << endl << "Eingabe beendet." << endl;
    }

    cout << endl << endl;
//TestMethods for Trie
    if (testTrieInsertAndFind()) {
        std::cout << "Test Insert() and Find() passed \n";
    } else {
        std::cout << "Test Insert() and Find() failed.\n";
    }
    if (testBeginAndEnd()) {
        std::cout << "Test Begin() and End() passed\n";
    } else {
        std::cout << "Test Begin() and End() failed.\n";
    }
    if (testUpperBound()) {
        std::cout << "Test Upper_Bound() passed\n";
    } else {
        std::cout << "Test Upper_Bound() failed.\n";
    }
    if (testIncrementInterator()) {
        std::cout << "Test testIncrementInterator() passed\n";
    } else {
        std::cout << "Test testIncrementInterator() failed.\n";
    }
    if (testErase()) {
        std::cout << "Test testErase() passed\n";
    } else {
        std::cout << "Test testErase() failed.\n";
    }


    return 0;
}