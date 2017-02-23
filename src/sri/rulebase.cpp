//
//  rulebase.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "rulebase.hpp"
void RuleBase::insertRule(bool isAND, string name, list<string> ruleParams, list<pair<string, list<string>>> facts) { //maps factnames to params
    if(rules.count(name)) {
        cout << "rule exists" << endl;
        return ;
    }
    
    Rule r;
    r.name = name;
    vector<Predicate> predicates;
    
    //RULE Master($X, $Y):- AND Father($X, $Y) Superior($X, $Y)
    
    for(auto fact: facts)
    {
        string factName = fact.first;
        list<Param> params;
        Predicate pred;// = new Predicate;
        pred.factName = factName;
        for(string paramNameForFact : fact.second) //fect.second is list of paramNames
        {
            Param p;
            p.assignName(paramNameForFact);
            params.push_back(p);
        }
        
        
        pred.params = params;
        
        predicates.push_back(pred);
       // for(Param& param : pred.params)
         //   predicates.back().params.push_back({param.name, param.isConst});
        
    }
    r.predicates = predicates;
    r.isAND = isAND;
    
    for(string paramNameForRule : ruleParams) //fect.second is list of paramNames
    {
        Param p;
        p.assignName(paramNameForRule);
        r.ruleParams.push_back(p);
    }
    
    rules[name] = r;
  
    
}

Rule RuleBase::getRule(string rule)
{
    //if(!rules.count(rule))
      //  return vector<list<string>>();
    cout << "Got rule: " << rule << endl;
    return rules[rule];
}

/*void RuleBase::printRules() {
    for(auto& rule: rules)
        for(auto& ruleBody: rule.second) {
            cout << rule.first;
            for(auto& fact: ruleBody)
                cout << "->" << fact;
            cout << endl;
        }
}*/

void RuleBase::dropRule(string rule) {
    if(!rules.count(rule)) {
        cout << "rule not exist" << endl;
        return ;
    }
    rules.erase(rule);
}

/*void RuleBase::writeToFile(ofstream& outfile)
{
    for(auto& rule: rules)
    {
        char param = 'A';
        outfile << "RULE " << rule.first << "($A, $B):- ";//will update this when $paramaters are updated
        if(rule.second.size() == 1)
        {
            outfile << "AND ";
            for(auto& ruleBody: rule.second)
            {
                for(auto& fact: ruleBody)
                {
                    outfile << " " << fact << "(" << "$"<< param++;
                    outfile << "," << "$"<<param << ")";
                }
            }
        }
        else
        {
            outfile << "OR ";
            for(auto& ruleBody: rule.second)
            {
                for(auto& fact: ruleBody)
                    outfile << " " << fact << "(" << "$"<<param << "," << "$"<<(char)(param+1) << ")";
            
            }
        }
        outfile << endl;
    }
}*/


