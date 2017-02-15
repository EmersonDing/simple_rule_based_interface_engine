//
//  sri.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "sri.hpp"
void SRI::queryRuleHelper(vector<vector<string>>& ret, vector<string>& row, const list<string>& rule, list<string>::iterator index, string start) {
    if(index == rule.end()) {
        ret.push_back(row);
        return ;
    }
    auto next = knowledgebase.queryRelation(*index, start);
    for(auto node: next) {
        row.push_back(node);
        queryRuleHelper(ret, row, rule, ++index, node);
        --index;
        row.pop_back();
    }
}

// calling parseStringInput() to parse string, call function of drop, insert
// in Base classes to execute query
void SRI::insertRule(string name, vector<list<string>> facts) {
    rulebase.insertRule(name, facts);
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

void SRI::queryRule(string _rule) {
    auto rule = rulebase.getRule(_rule);
    if(rule.empty()) {
        cout << "rule not exist" << endl;
    }
    vector<vector<string>> ret;
    for(auto& r: rule) {
        auto front = knowledgebase.queryRelation(r.front());
        for(auto& f: front) {
            vector<string> row(1, f.first);
            row.push_back(f.second);
            queryRuleHelper(ret, row, r, next(r.begin(),1), f.second);
        }
    }
    // print name
    for(auto row: ret) {
        cout << row.front() << '\t' << row.back() << endl;
    }
}
