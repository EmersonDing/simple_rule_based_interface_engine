//
//  sri.hpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#ifndef sri_hpp
#define sri_hpp

#include <fstream> //for file operations
#include <sstream>

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
    
    
    bool backtrack(unordered_map<string, vector<string>>& currentParamAssignments, unordered_set<string>& params, Predicate pred);
    
    bool checkAssignments(Predicate& predicate, string nodeName, unordered_map<string, string>&currentParamAssignments, Rule& rule);
    
    void parseStringInput();		// parse input string
    void parseStringOutput();		// parse output string
    void queryRuleHelper(vector<vector<string>>& ret, vector<string>& row, const list<string>& rule, list<string>::iterator index, string start);
    KnowledgeBase knowledgebase;
    RuleBase rulebase;
public:
    void executeQuery(string input);    // TODO
    void load(const string& path);			// load rules and facts. TODO
    void dump(const string& path = "out.txt");			// dump rules and facts. TODO
    void insertRule(bool isAND, string name, list<string> rParams, list<pair<string, list<string>>> facts);
    void dropRule();
    //void printRule();
    void insertFact(string relation, string subject, string object);
    void printGraph();
    void dropFact(string relation, string subject, string object);
    void queryRule(string _rule);
};

