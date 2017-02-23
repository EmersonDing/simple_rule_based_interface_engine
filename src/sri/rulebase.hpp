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


class Rule {
    bool isAnd;
    string name;
    pair<string, string> startEnd; // params for rule. not necessary,
    unordered_map<string, vector<pair<string, string>>> ruleGraph;   // {"X":{"Father", "Y"}}
    
    void insertRuleGraph(vector<pair<string, pair<string, string>>> params) {
        for(auto row: params)
            ruleGraph[row.second.first].push_back({row.first, row.second.second});
    }
    
public:
    Rule() {
        // TODO
    }
    
    Rule(string _name, bool _isAnd, pair<string, string> _startEnd, vector<pair<string, pair<string, string>>> _params): name(_name), isAnd(_isAnd), startEnd(_startEnd) {
        insertRuleGraph(_params);
    }
    
    void print() {
        cout << startEnd.first << " to " << startEnd.second << endl;
        for(auto rule: ruleGraph)
            for(auto subRule: rule.second)
                cout << rule.first << " " << subRule.first << " " << subRule.second << endl;
    }
};

class RuleBase {
    unordered_map<string, Rule> rules;  // each list<string> will be regard as a relationship chain
public:
    void insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params);   // if a new rule is relied on another rule, replace input list with that rule. TODO
    void dropRule(string rule);
    Rule getRule(string rule);
    void printRules();
};