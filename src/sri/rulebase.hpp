//
//  rulebase.hpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#ifndef rulebase_hpp
#define rulebase_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;
#endif /* rulebase_hpp */


struct Rule {
    bool isAnd;
    string name;
    pair<string, string> params; // params for rule. not necessary,
    unordered_map<string, unordered_set<string>> ruleGraph;
};

class RuleBase {
    unordered_map<string, Rule> rules;  // each list<string> will be regard as a relationship chain
public:
    void insertRule(string name, vector<list<string>> facts);   // if a new rule is relied on another rule, replace input list with that rule. TODO
    void dropRule(string rule);
    vector<list<string>> getRule(string rule);
    void printRules();
};