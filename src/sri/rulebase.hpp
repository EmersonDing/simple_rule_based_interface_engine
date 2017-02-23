//
//  rulebase.hpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#ifndef rulebase_hpp
#define rulebase_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>
using namespace std;
#endif /* rulebase_hpp */



struct Param
{
    string name;
    bool isConst;
    void assignName(string n)
    {
        if(n[0] == '$')
        {
            name = n[1]; //name will only be varibale letter in $A, 'A'
            isConst = false;
        }
        else
        {
            name = n;
            isConst = true;
        }
        
    }
};
struct Predicate
{
    string factName;
    list<Param> params; //$A, $B for example
    Predicate(const Predicate& pred)
    {
        //cout << "COPY\n";
        factName=pred.factName;
        for(Param param : pred.params)
            params.push_back(param);
    }
    Predicate()
    {
        
    }
};

struct Rule
{
    bool isAND;n
    string name;
    list<Param> ruleParams;
    vector<Predicate> predicates;
    
};

class RuleBase {
    unordered_map<string, Rule> rules;  // each list<string> will be regard as a relationship chain
    //unordered_map<string, vector<list<string>>> ruleParams;
public:
    void insertRule(bool isAND, string name, list<string> params, list<pair<string, list<string>>> facts);   // if a new rule is relied on another rule, replace input list with that rule. TODO
    void dropRule(string rule);
    Rule getRule(string rule);
    void printRules();
    
    //void writeToFile(ofstream& outfile);
};
