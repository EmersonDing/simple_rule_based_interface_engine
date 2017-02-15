//
//  rulebase.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "rulebase.hpp"
void RuleBase::insertRule(string name, vector<list<string>> facts) {
    if(rules.count(name)) {
        cout << "rule exists" << endl;
        return ;
    }
    for(auto fact: facts)
        rules[name].push_back(fact);
}

vector<list<string>> RuleBase::getRule(string rule) {
    if(!rules.count(rule))
        return vector<list<string>>();
    return rules[rule];
}

void RuleBase::printRules() {
    for(auto& rule: rules)
        for(auto& ruleBody: rule.second) {
            cout << rule.first;
            for(auto& fact: ruleBody)
                cout << "->" << fact;
            cout << endl;
        }
}

void RuleBase::dropRule(string rule) {
    if(!rules.count(rule)) {
        cout << "rule not exist" << endl;
        return ;
    }
    rules.erase(rule);
}