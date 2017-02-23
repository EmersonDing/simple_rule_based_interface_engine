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
void SRI::insertRule(bool isAND, string name, list<string> rParams, list<pair<string, list<string>>> facts) {
    rulebase.insertRule(isAND, name, rParams, facts);
}

/*void SRI::printRule() {
    rulebase.printRules();
}*/

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
    Rule rule = rulebase.getRule(_rule);
    /*if() {
        cout << "rule not exist" << endl;
    }*/
    
    unordered_map<string, vector<string>> currentParamAssignments; //key is param, i.i 'A', vector is possible fits for this param
    
    unordered_set<string> params; //set of all params involved in this rule
    for(Predicate predicate : rule.predicates)
    {
    
        for(Param param : predicate.params)
        {
            params.insert(param.name);
        }
    }
    
    vector<string> ruleParams; //contains A, C for grandfather
    for(Param param : rule.ruleParams)
        ruleParams.push_back(param.name);

    
    
    for(string param : params)
    {
        
        //cout << param << endl;
    }
    
    vector<pair<string, string>> initialSatisfiers;
    
    
    for(Predicate& predicate : rule.predicates)
    {
        string paramFront = predicate.params.front().name;
        string paramBack = predicate.params.back().name;
        string factName = predicate.factName;
        //vector<pair<string, string>> KnowledgeBase::queryRelation(string _relation)
        if(!currentParamAssignments.count(paramFront) && !currentParamAssignments.count(paramBack)) //if this param has not been assigned anything yet, find all relations that satsify the factName
        {

            initialSatisfiers = knowledgebase.queryRelation(factName);
            for(pair<string, string> factPair : initialSatisfiers)
            {
                currentParamAssignments[paramFront].push_back(factPair.first);
                currentParamAssignments[paramBack].push_back(factPair.second);
                
                
            }
        }
        else if(!currentParamAssignments.count(paramBack)) // SA constant
        {
            
            vector<string> possiblePredicateSatisfiers;
            vector<string> preds = currentParamAssignments[paramFront]; //use this for the loop, that way we won't modify elements of this temp var before using them in the loop
            for(string predSatisfier : preds)//currentParamAssignments[paramFront])
            {
                
                cout << "Pred: " << predSatisfier << endl;
                
                vector<string>relations = knowledgebase.queryRelation(factName, predSatisfier );
                
                for(string p : relations)
                    possiblePredicateSatisfiers.push_back(p);
                if(!relations.size())
                {//if no facts that satisfy with this assignment, remove it from options
                    currentParamAssignments[paramFront].erase(std::remove(currentParamAssignments[paramFront].begin(), currentParamAssignments[paramFront].end(), predSatisfier), currentParamAssignments[paramFront].end());
                    /*cout << "After DELETION\n";

                    for(string assignment : currentParamAssignments[paramFront])
                            cout << paramFront << " " << assignment << endl;
                    cout << "*****\n";*/
                    
                }
            }
            for(string& factObj : possiblePredicateSatisfiers)
            {
                currentParamAssignments[paramBack].push_back(factObj);
                
            }
            
        }
        else if(!currentParamAssignments.count(paramFront)) //constant $B
        {
            
        }
      
        
    }
    
    /*for(Param param : rule.ruleParams)
    {
        for(string assignment : currentParamAssignments[param.name])
            cout << param.name << " " << assignment << endl;
    }*/
    for(string param : params)
    {
        for(string assignment : currentParamAssignments[param])
            cout << param << " " << assignment << endl;
    }
   
    
    //cout << currentParamAssignments["C"].back();
    
}









std::vector<std::string> tokenize(std::string& s, bool isRule)
{
    std::vector<std::string> parsedString;
    
    char nextChar;
    std::string st;
    int i = 0;
    
    while(i < s.length())
    {
        nextChar = s[i++];
        if(nextChar == ' ' )
            continue; //ignore whitespace
        
        else if( isRule && nextChar == '(') //when parsing rules, parantheses are considered in a different way
        {
            while(nextChar != ')')
                nextChar = s[i++]; //will add more later to consider variables preceded by $, for now
        }
        
        
        if(nextChar == ',' || nextChar == '(' || nextChar == ')' || nextChar == ':' || nextChar == '-')
        {
            if (!st.length()) //do not add blank strings
                continue;
            parsedString.push_back(st);
            st.erase(); //reset st so we can get next parsed element
            continue;
        }
        st += nextChar;
        
        
    }
    
    return parsedString;
}




/*void SRI::load(const string& path)
{
    std::ifstream file;
    file.open(path);
    if(!file.is_open())
    {
        std::cout << "Failed to load from file " << path << std::endl;
        return;
    }
    
    std::string currentLine;
    while(std::getline(file, currentLine)) //read next line from file into string currentLine unil EOF
    {
        std::stringstream stream(currentLine);
        //s.insertFact("Father", "Mark", "Greg");
        
        std::string type;
        stream >> type;
        if(type == "FACT")
        {
            std::string factDef;
            std::string factDefParts; //in case there is whitespace between params in definition of fact
            while(stream >> factDefParts)
            {
                factDef.append(factDefParts);
            }
           // std::cout << "FactDef: " << factDef << std::endl;
            std::vector<std::string> factInfo = tokenize(factDef, false); //second param is isRule
            //for(std::string param : factInfo)
              //  std::cout << param << " ";
            std::cout << "\n";
            
            insertFact(factInfo[0], factInfo[1], factInfo[2]);
            
        }
        else if(type == "RULE")
        {
            std::string ruleDef;
            std::string ruleDefParts; //in case there is whitespace between params in definition of fact
            
            std::string logicalRelation; //AND or OR
            
            while(stream >> ruleDefParts)
            {
                if(ruleDefParts == "AND" || ruleDefParts == "OR")
                {
                    logicalRelation = ruleDefParts;
                    continue;
                }
                ruleDef.append(ruleDefParts);
            }
    
            
            if(logicalRelation == "AND")
            {
                list<string> rule;
                for(int i = 1; i < ruleInfo.size(); i++)
                {
                    rule.push_back(ruleInfo[i]);
                }
                
                insertRule(ruleInfo[0], {rule});    // When AND, the vector will only contain one rule
            }
            else if(logicalRelation == "OR")
            {
                std::vector<list<string>> rules;
                for(int i = 1; i < ruleInfo.size(); i++)
                {
                    list<string>rule;
                    rule.push_back(ruleInfo[i]);
                    rules.push_back(rule);

                }
                insertRule(ruleInfo[0], rules); // When OR, the vector will contain multiple lists of rules
                //s.insertRule("Parent", {{"Father"}, {"Mother"}});   // Parent is OR, two list
            }
            else
            {
                cout << "Invalid logical relation. Must be AND/OR. Rule not loaded from file" << endl;
            }
            
            
        }
        
        
        
    }
}*/

void SRI::dump(const string& path) //defaults to out.txt
{
   
    std::ofstream outfile(path);

    knowledgebase.writeToFile(outfile);
    //rulebase.writeToFile(outfile);

    
    outfile.close();
}





