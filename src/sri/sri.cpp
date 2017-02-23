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
    
    unordered_map<string, string> currentParamAssignments; //key is param, i.i 'A', vector is possible fits for this param
    
    unordered_set<string> params;
    for(Predicate predicate : rule.predicates)
    {
    
        for(Param param : predicate.params)
        {
            params.insert(param.name);
        }
    }
    
    
    for(string param : params)
    {
        
        //cout << param << endl;
    }
    

    
    //for(Predicate& predicate : rule.predicates)
    //for(auto node : knowledgebase.graph)
    {
  
        Predicate predicate = rule.predicates[0];
        
        string factName = predicate.factName;
        for(auto node : knowledgebase.graph)
        {
           
           
            
            string nodeName = node.first;
            auto nodeRelations = knowledgebase.graph[nodeName].relation;
            //while( i < rule.predicates.size() && checkAssignments( predicate, nodeName, currentParamAssignments, i, rule) ) //if there are nodes related through given predicate, perform following logic
            for(Predicate predicate : rule.predicates)
            {
                string p = predicate.params.front().name;
                if(currentParamAssignments.count(p))
                {
                    nodeName = currentParamAssignments[p]; //if param already assigned, use this assignment
                    cout << "ASSIGNED " << nodeName << " for " << p << endl;
                    
                }
                
                if(!checkAssignments( predicate, nodeName, currentParamAssignments, rule))
                    break;
                
                
            }
            currentParamAssignments.clear();
        }
    }
    
    //cout << predicateParams["A"].back();
    //cout << predicateParams["B"].back();
    
    //vector<vector<string>> ret;
    /*for(auto& r: rule) {
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
    }*/
}




bool SRI::checkAssignments(Predicate& predicate, string nodeName, unordered_map<string, string>&currentParamAssignments, Rule& rule)
{
    //cout << knowledgebase.isFact("Father", "Mark", "Greg");
    string paramFront = predicate.params.front().name;
    string paramBack = predicate.params.back().name;
    string factName = predicate.factName;
    
   // for(auto node : knowledgebase.graph)
    {
        
        auto nodeRelations = knowledgebase.graph[nodeName].relation;
        if(nodeRelations[factName].size()) //if there are nodes related through given predicate, perform following logic
        //if(knowledgebase.isFact(factName, nodeName, nodeObj))
        {
            cout << "There is a " << factName << " named " << nodeName << endl;
            auto relations  = nodeRelations[factName];
            currentParamAssignments[paramFront] = nodeName; // $A
            
            //add either paramter of vector<string> or return this, for potential objects i.e sons of father
            //pop_back() in query
            
            //currentParamAssignments[paramBack] = nodeName;
            
            /*for(string relation : relations)
            {
                currentParamAssignments[paramBack] = relation; //person related to nodeName
                
                i++;
                predicate = rule.predicates[i];
                
                
               // predicateParams[paramFront].push_back(relation);
                //predicateParams[paramBack].push_back(nodeName);
                
            }*/
            return true;
            
        }
    }
    
    
   
    
     
    return false;
}


bool assignmentComplete(unordered_map<string, vector<string>>& currentParamAssignments, unordered_set<string>& params)
 {
 for(auto param : params)
 {
 if(!currentParamAssignments.count(param))
 return false; //if there is an unassigneed variable, return false
 }
 return true;
 }


bool SRI::backtrack(unordered_map<string, vector<string>>& currentParamAssignments, unordered_set<string>& params, Predicate predicate)
 {
     if(assignmentComplete(currentParamAssignments, params))
         return true;
 
     //Predicate predicate; '' = rule.predicates;
     
     string paramFront = predicate.params.front().name;
     string paramBack = predicate.params.back().name;
     string factName = predicate.factName;
     
     for(string assignemnt : currentParamAssignments[paramBack])
     {
         
         if(backtrack(currentParamAssignments,  params,predicate))
         {
             
         }
     }
 
 
     for(auto node : knowledgebase.graph)
     {
     string nodeName = node.first;
         auto nodeRelations = knowledgebase.graph[nodeName].relation;
     }
 
 
     return false;
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





