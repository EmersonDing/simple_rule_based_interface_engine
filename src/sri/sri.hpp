/*
 sri.hpp
 Group 9
 This class is used to model an SRI and handles all command line input. It contains a rule and knowledgebase which
 are used to make inferences.It also uses InputParser.hpp to help simplify the logic of parsing strings 
 */

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
#include <thread>
#include <mutex>
#include "knowledge.hpp"
#include "rulebase.hpp"

#include "InputParser.hpp"

using namespace std;
#endif /* sri_hpp */





class SRI {
    
    
    
    
   
    void parseStringOutput();		// parse output string
    vector<pair<string, string>> queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e);
    void querySingleRule(const pair<string, string>& edge, const string& s, const string& e, const string& start, const string& end, const Rule& rule, bool isFirstEdge, unordered_set<string>& dict, unordered_set<string>& visited, mutex& lock_dict);
    KnowledgeBase knowledgebase;
    RuleBase rulebase;
    mutex lock_print;   // printing lock
public:
    
    void parseAndInsertRule(string rule, bool logOp); //used to simplify code when parsing input and inserting
    
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
    
    void dropInferenceFacts(string facts); //used to drop facts created as the result of an inference
};

