//
//  sri.hpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#ifndef sri_hpp
#define sri_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "knowledge.hpp"
#include "rulebase.hpp"
using namespace std;
#endif /* sri_hpp */


class SRI {
    void parseStringInput();		// parse input string
    void parseStringOutput();		// parse output string
    vector<pair<string, string>> queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e);
    RuleBase rulebase;
public:
    KnowledgeBase knowledgebase;
    void executeQuery(string input);    // TODO
    void load();			// load rules and facts. TODO
    void dump();			// dump rules and facts. TODO
    void insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params);
    void dropRule();
    void printRule();
    void insertFact(string relation, string subject, string object);
    void printGraph();
    void dropFact(string relation, string subject, string object);
    vector<pair<string, string>> queryRule(string _rule, string start = "", string end = "");
};

