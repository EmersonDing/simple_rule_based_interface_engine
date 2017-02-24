//
//  sri.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "sri.hpp"
//void SRI::queryRuleHelper(vector<vector<string>>& ret, vector<string>& row, const list<string>& rule, list<string>::iterator index, string start) {
//    if(index == rule.end()) {
//        ret.push_back(row);
//        return ;
//    }
//    auto next = knowledgebase.queryRelation(*index, start);
//    for(auto node: next) {
//        row.push_back(node);
//        queryRuleHelper(ret, row, rule, ++index, node);
//        --index;
//        row.pop_back();
//    }
//}

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

vector<pair<string, string>> SRI::queryRuleHelper(string start, string end, vector<pair<string, string>> row, unordered_set<string>& visited, string s, string e) {
    if(start == end)
        return row;
    if(visited.count(start))
        return vector<pair<string, string>>();
    vector<pair<string, string>> ret;
    visited.insert(start);
    auto rule = rulebase.getRule(start);
    if(rule.isAnd) {
        for(auto& neighbor_node: rule.ruleGraph) {
            for(auto& edge: neighbor_node.second) {
                string relation = edge.first;
                vector<pair<string, string>> r;
                if(knowledgebase.graph.count(relation)) {
                    r = knowledgebase.queryRelation(relation, start);
                    
                    for(auto& e: r) {
                        auto sub = queryRuleHelper(, <#string end#>, <#vector<pair<string, string> > row#>, <#unordered_set<string> &visited#>, <#string s#>, <#string e#>)
                    }
                }
                else
                    r = queryRule(relation, s, e);
                // put in dict
            }
        }
    } else {
        
    }
    
    
    visited.erase(start);
    return ret;
}

vector<pair<string, string>> SRI::queryRule(string _rule, string start, string end) {
    vector<pair<string, string>> ret;
    unordered_set<string> visited;
    ret = queryRuleHelper("X", "Y", ret, visited, start, end);
    return ret;
}

//void SRI::queryRule(string _rule, vector<string> filter) {
//    auto rule = rulebase.getRule(_rule);
//    if(rule == Rule()) {
//        cout << "rule not exist" << endl;
//    }
//    vector<vector<string>> ret;
//    for(auto& r: rule) {
//        auto front = knowledgebase.queryRelation(r.front());
//        for(auto& f: front) {
//            vector<string> row(1, f.first);
//            row.push_back(f.second);
//            queryRuleHelper(ret, row, r, next(r.begin(),1), f.second);
//        }
//    }
//    // print name
//    for(auto row: ret) {
//        for(int i = 0; i < filter.size(); ++i)
//            if(filter[i] != "#" && filter[i] != row[i])
//                goto notPrint;
//        cout << row.front() << '\t' << row.back() << endl;
//        notPrint:;
//    }
//}
