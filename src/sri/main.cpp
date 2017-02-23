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
    s.insertFact("Superior", "Mark", "Greg");
    s.insertFact("Father", "Mark", "Stanley");
    s.insertFact("Father", "John", "Mark");
    s.insertFact("Mother", "Marry", "Stanley");
    s.insertFact("Father", "Stanley", "Lucy");
    s.insertFact("Mother", "Jane", "Mark");
    s.insertFact("Parent", "Greg", "Jim");
    
    // drop facts
    s.dropFact("Mother", "Marry", "Stanley");
    
    // print facts
    s.printGraph();
    cout << "****" << endl << endl;
    
    // insert rules
    list<pair<string, list<string>>> gfFacts;

    gfFacts.push_back({"Father" ,{"$A", "$B"}});
    gfFacts.push_back({"Parent" ,{"$B", "$C"}});

    
    
    s.insertRule(true, "Grandfather", {"$A", "$C"}, gfFacts);    // GrandFather is AND, hence one list, Father to Father
    s.insertRule(true, "Master", {"$A", "$B"}, {{"Father" ,{"$A", "$B"}}, {"Superior" ,{"$A", "$B"}}});//notice new way of adding rules
    
    
    //s.queryRule("Master");
    s.queryRule("Grandfather");//this isn't quite working, needs a LOT of work!!!!!!!
    
    
    
    
    
    
    /*
    
    s.load("InputFile.txt");
    s.printGraph();
    s.printRule();
    
    s.dump();
    
    cout << "****" << endl << endl;*/
    
    return 0;
}
