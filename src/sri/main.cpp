/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "sri.hpp"



using namespace std;

template <typename T>
void printPair(vector<pair<T, T>> p) {
    for(auto& line: p)
        cout << line.first << '\t' << line.second << endl;
}



int main(int argc, const char * argv[]) {
    
    SRI s;
    // insert facts
    s.insertFact("Father", "Mark", "Greg");
    s.insertFact("Father", "Mark", "Stanley");
    s.insertFact("Father", "John", "Mark");
    s.insertFact("Mother", "Marry", "Stanley");
    s.insertFact("Father", "Stanley", "Lucy");
    s.insertFact("Mother", "Jane", "Mark");
    s.insertFact("Father", "Greg", "David");
    
    // drop facts
    //    s.dropFact("Mother", "Marry", "Stanley");
    
    // print facts
    //    s.printGraph();
    //    cout << "****" << endl << endl;
    
    // insert rules
    s.insertRule("Grandfather", {"X", "Y"}, true, {{"Father", {"X", "Z"}}, {"Father", {"Z", "Y"}}});
    s.insertRule("Parent", {"X", "Y"}, false, {{"Father", {"X", "Y"}}, {"Mother", {"X", "Y"}}});
    s.insertRule("GrandParent", {"X", "Y"}, true, {{"Parent", {"X", "Z"}}, {"Parent", {"Z", "Y"}}});
    s.insertRule("GrandGrandFather", {"X", "Y"}, false, {{"Father", {"X", "Z"}}, {"GrandParent", {"Z", "Y"}}});
    //    s.printRule();
    
    
    // query rules
    //    printPair(s.queryRule("Father"));   // all father fact
    //    cout << "****" << endl;
    //    printPair(s.queryRule("Father", "Mark"));   // Father: "Mark", "$"
    //    cout << "****" << endl;
    //    printPair(s.queryRule("Father", "", "Greg"));   // Father: "$", "Greg"
    //    cout << "****" << endl;
    //    printPair(s.queryRule("Parent"));   // Parent: "$", "$"
    //    cout << "****" << endl;
    //    printPair(s.queryRule("Parent", "John"));   // Parent: "$", "John"
    //    cout << "****" << endl;
    //    printPair(s.queryRule("GrandParent"));  // GrandParent: "$", "$"
    //    cout << "****" << endl;
    //    printPair(s.queryRule("GrandParent", "John"));  // GrandParent: "$", "John"
    //    cout << "****" << endl;
    printPair<string>(s.queryRule("GrandGrandFather", "John")); // GrandGrandFather: "$", "John"
    cout << "****" << endl;

    return 0;
}
