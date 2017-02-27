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

#include "InputParser.hpp"

using namespace std;
#endif /* sri_hpp */





class SRI {
    
    
    
    
   
    void parseStringOutput();		// parse output string
    vector<pair<string, string>> queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e);
    KnowledgeBase knowledgebase;
    RuleBase rulebase;
public:
    
    void parseAndInsertRule(string rule, bool logOp);
    
    void parseInput(string input);		// parse input string
    vector<pair<string, string>> queryRule(string _rule, string start = "", string end = "");
    void load(const string& path);			// load rules and facts.
    void dump(const string& path = "out.txt");			// dump rules and facts. 
    void insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params);
    void printRule();
    void insertFact(string relation, string subject, string object);
    void printGraph();
    void dropFact(string relation, string subject, string object);
    
    void dropRule(string rule);
    
    void queryRule(string _rule);
    
    void dropInferenceFacts(string facts);
};

