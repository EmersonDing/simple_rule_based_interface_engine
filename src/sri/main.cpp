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
    
    // drop facts
    s.dropFact("Mother", "Marry", "Stanley");
    
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
//    s.queryRule("Grandfather", {});
//    cout << "****" << endl;
//    s.queryRule("Grandgrandfather", {});
//    cout << "****" << endl;
//    s.queryRule("Parent", {});
//    cout << "****" << endl;
//    s.queryRule("GrandParent", {"#", "Stanley", "#"});     // first name filter with "John"
//    cout << "****" << endl << endl;
    
    return 0;
}
