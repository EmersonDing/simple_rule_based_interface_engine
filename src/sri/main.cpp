//
//  main.cpp
//  sri
//
//  Created by Emerson on 2/14/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "sri.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    SRI s;
    // insert facts
    s.insertFact("Father", "Mark", "Greg");
    s.insertFact("Father", "Mark", "Stanley");
    s.insertFact("Father", "John", "Mark");
    s.insertFact("Mother", "Marry", "Stanley");
    s.insertFact("Father", "Stanley", "Lucy");
    s.insertFact("Mother", "Jane", "Mark");
    s.insertFact("Parent", "Mark", "Greg");
    
    // drop facts
    s.dropFact("Mother", "Marry", "Stanley");
    
    // print facts
    s.printGraph();
    cout << "****" << endl << endl;
    
    // insert rules
    list<pair<string, list<string>>> gfFacts;
    //RULE GodFather($X,$Y):- AND Friend($X,$Z) Parent($Z,$Y)
    gfFacts.push_back({"Father" ,{"$A", "$B"}});
    gfFacts.push_back({"Parent" ,{"$B", "$C"}});
    //gfFacts["Father"] = {"$A", "$B"};
    
    
    s.insertRule(true, "Grandfather", {"$A", "$B"}, gfFacts);    // GrandFather is AND, hence one list, Father to Father
    s.queryRule("Grandfather");
    /*s.insertRule("Grandgrandfather", {{"Father", "Father", "Father"}}); // one list
    s.insertRule("Parent", {{"Father"}, {"Mother"}});   // Parent is OR, two list
    s.insertRule("GrandParent", {{"Father", "Father"}, {"Father", "Mother"}, {"Mother", "Father"}, {"Mother", "Mother"}});  // GrandParent is OR mixed with AND, four list
    
    // query rules
    s.queryRule("Grandfather");
    cout << "****" << endl;
    s.queryRule("Grandgrandfather");
    cout << "****" << endl;
    s.queryRule("Parent");
    cout << "****" << endl;
    s.queryRule("GrandParent");
    
    s.load("InputFile.txt");
    s.printGraph();
    s.printRule();
    
    s.dump();
    
    cout << "****" << endl << endl;*/
    
    return 0;
}
