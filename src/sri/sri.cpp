//
//  sri.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "sri.hpp"
// calling parseStringInput() to parse string, call function of drop, insert
// in Base classes to execute query
void SRI::insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params) {
    rulebase.insertRule(name, startEnd, isAnd, params);
}

void SRI::printRule() {
    rulebase.printRules();
}

void SRI::insertFact(string relation, string subject, string object) {
    knowledgebase.insertFact(relation, subject, object);
}

void SRI::printGraph() {
    knowledgebase.printGraph();
}

void SRI::dropFact(string relation, string subject, string object) {
    knowledgebase.dropFact(relation, subject, object);
}

vector<pair<string, string>> SRI::queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e) {
    if(start == end)
        return {{"", s}};
    if(visited.count(start))
        return vector<pair<string, string>>();
    vector<pair<string, string>> ret;
    bool isFirstEdge = false;
    visited.insert(start);
    unordered_set<string> dict;
    for(auto& edge: rule.ruleGraph[start]) {
        string relation = edge.first;
        vector<pair<string, string>> r;
        vector<pair<string, string>> _row;
        if(knowledgebase.knowledge_dict.count(relation)) {
            r = knowledgebase.queryRelation(relation, s);
        }
        else {
            r = queryRule(relation, s, e);
        }
        for(auto& _r: r) {
            auto t = queryRuleHelper(rule, edge.second, end, visited, _r.second, e);
            _row.insert(_row.end(), t.begin(), t.end());
        }
        if(!isFirstEdge || !rule.isAnd) {   // if is OR
            isFirstEdge = true;
            for(auto& _r: _row)
                if(s == "")
                    dict.insert(_r.first + " " + _r.second);
                else
                    dict.insert(s + " " + _r.second);
        } else {
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
    for(auto& str: dict)
        ret.push_back({str.substr(0, str.find(' ')), str.substr(str.find(' ')+1)});
    visited.erase(start);
    return ret;
}

vector<pair<string, string>> SRI::queryRule(string _rule, string start, string end) {
    vector<pair<string, string>> ret;
    unordered_set<string> visited;
    Rule rule = rulebase.getRule(_rule);
    ret = queryRuleHelper(rule, rule.startEnd.first, rule.startEnd.second, visited, start, end);
    return ret;
}
