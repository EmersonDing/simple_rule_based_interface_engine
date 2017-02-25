//
//  rulebase.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//
#include "rulebase.hpp"
void RuleBase::insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params) {
    if(rules.count(name)) {
        cout << "rule exists" << endl;
        return ;
    }
    Rule rule(name, isAnd, startEnd, params);
    rules[name] = rule;
}

Rule RuleBase::getRule(string rule) {
    if(!rules.count(rule))
        return Rule();
    return rules[rule];
}

void RuleBase::printRules() {
    for(auto& rule: rules) {
        cout << rule.first << endl;
        rule.second.print();
    }
}

void RuleBase::dropRule(string rule) {
    if(!rules.count(rule)) {
        cout << "rule not exist" << endl;
        return ;
    }
    rules.erase(rule);
}

void RuleBase::writeToFile(ofstream& outfile)
{
    for(auto& rule: rules)
    {
        Rule r = rule.second;
        
        outfile << "RULE " << rule.first << "($" << r.startEnd.first << ",$" << r.startEnd.second << "):- ";
        
        if(r.isAnd)
            outfile << "AND ";
        else
            outfile << "OR ";
        
    
        for(auto& rulePredicate : r.ruleGraph)
        {

            string leftParam = rulePredicate.first;
            vector<pair<string, string>> paramDependencies = rulePredicate.second;
            
            for(auto dependency : paramDependencies)
            {
                outfile << dependency.first << "($" << leftParam << ",$" << dependency.second << ") ";
            }
            
        }
       
        outfile << endl;
    }
}



