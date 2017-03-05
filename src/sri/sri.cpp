//
//  sri.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "sri.hpp"
/*
 * query result of a rule
 * rule - rule to query; start - start node of rule, e.g. $X; end - end node of rule
 * visited - visited node in a rule graph; s, e - two variables of query sentence. e.g. for Father("Mark", "John"), s == "Mark" and e == "John". empty string as default
 * The function works as dfs. For a rule r, all neighbors will be find at first, and neighbor rule/fact will be queried, and another dfs function will be called based on the result of first neighbor layer. Function returns when start equals to end
 */
vector<pair<string, string>> SRI::queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e) {
    if(start == end)    // base case
        return {};
    if(visited.count(start))    // if already visited, return empty result
        return vector<pair<string, string>>();
    vector<pair<string, string>> ret;
    bool isFirstEdge = false;   // for "AND" relationship, all results from different neighbors will be merged and only result exist in all neighbor result will be left. first neighbor will be a special case
    visited.insert(start);  // changed visited
    unordered_set<string> dict; // temperarily save result from different neighbor and used to erase result not following "AND" and "OR" rule
    // traverse the nrighbors
    for(auto& edge: rule.ruleGraph[start]) {
        string relation = edge.first;   // rule/fact name
        vector<pair<string, string>> r; // temp variable to get result from next level of dfs
        vector<pair<string, string>> _row;  // temp variable to merge result from all levels of dfs
        if(knowledgebase.knowledge_dict.count(relation)) {
            r = knowledgebase.queryRelation(relation, s, e);
        }
        else {
            r = queryRule(relation, s, e);
        }
        if(edge.second != end)
            for(auto& _r: r) { // use dfs to query result of all of the relationships from current level
                auto t = queryRuleHelper(rule, edge.second, end, visited, _r.second, e);
                for(auto& _t: t)
                    if(s == "") _t.first = _r.first;
                    else _t.first = s;
                _row.insert(_row.end(), t.begin(), t.end());
            }
        else
            _row = r;
        if(!isFirstEdge || !rule.isAnd) {   // if is OR or first neighbor, directly insert _row into dict
            isFirstEdge = true;
            for(auto& _r: _row)
                if(s == "")
                    dict.insert(_r.first + " " + _r.second);
                else
                    dict.insert(s + " " + _r.second);
        } else {    // if is AND, only insert into dict when result head edge is already in dict
            unordered_set<string> dict_temp;
            for(auto& _r: _row) {
                string str;
                if(s == "")
                    str = _r.first + " " + _r.second;
                else
                    str = s + " " + _r.second;
                if(dict.count(str)) dict_temp.insert(str);
            }
            dict = dict_temp;
        }
    }
    for(auto& str: dict) {
        string str1 = str.substr(0, str.find(' ')), // head of a result relation
        str2 = str.substr(str.find(' ')+1);         // rear of a result relation
        if(e == "" || e == str2)
            ret.push_back({str1, str2});    // insert into ret
    }
    visited.erase(start);   // reset visited
    return ret; // final result
}


void SRI::insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params)
{
    rulebase.insertRule(name, startEnd, isAnd, params); // call function from rulebase
}


void SRI::printRule() {
    rulebase.printRules(); // call function from rulebase
}

void SRI::insertFact(string relation, string subject, string object) {
    knowledgebase.insertFact(relation, subject, object); // call function from knowledgebase
}

void SRI::printGraph() {
    knowledgebase.printGraph(); // call function from knowledgebase
}

void SRI::dropFact(string relation, string subject, string object) {
    knowledgebase.dropFact(relation, subject, object); // call function from knowledgebase
}

void SRI::dropRule(string rule)
{
    rulebase.dropRule(rule);     // call function from rulebase
}

vector<pair<string, string>> SRI::queryRule(string _rule, string start, string end) {
    vector<pair<string, string>> ret;   // return variable
    if(!knowledgebase.knowledge_dict.count(_rule)) {    // if _rule is a rule, use queryRuleHelper to get result
        unordered_set<string> visited;
        Rule rule = rulebase.getRule(_rule);
        ret = queryRuleHelper(rule, rule.startEnd.first, rule.startEnd.second, visited, start, end);
    } else
        ret = knowledgebase.queryRelation(_rule, start, end);   // if _rule is a fact, calling knowledge query function
    return ret;
}
