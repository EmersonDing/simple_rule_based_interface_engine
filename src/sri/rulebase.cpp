/*
 Rulebase.cpp
 Group 9
 */
#include "rulebase.hpp"
void RuleBase::insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params) {
    if(rules.count(name)) {
        cout << "rule " << name << " already exists" << endl;
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
    //write rules in the format specified by the project description 
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

bool RuleBase::isRule(string rule)
{
    return rules.count(rule);
}

