//
//  main.cpp
//  sri
//
//  Created by Emerson on 2/14/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

class FactNode {
public:
//    string name;	// name of a People. e.g. "Mark"
    // all relations of a people
    // e.g. {{"Father", {Peter"}}, {"Brother", {"John"}}}
    // means Father(Mark,Peter), Brother(Mark,John)
    unordered_map<string, unordered_set<string>> relation;
};
    
class KnowledgeBase {
    unordered_map<string, FactNode> graph;		// store people and their relations
public:
    void insertFact(string relation, string subject, string object) {
        // if relation already exists
        if(graph.count(subject) && graph[subject].relation.count(object)) {
            cout << "relationship already exist." << endl;
            return ;
        }
        graph[subject].relation[relation].insert(object);
    }
    void dropFact(string relation, string subject, string object) {
        if(!graph.count(subject) || !graph[subject].relation.count(relation) || !graph[subject].relation[relation].count(object)) {
            cout << "no such relationship." << endl;
            return ;
        }
        graph[subject].relation[relation].erase(object);
    }
    void printGraph() {
        for(auto& subject: graph)
            for(auto& relation: subject.second.relation)
                for(auto& object: relation.second)
                    cout << relation.first << ": " << subject.first << "," << object << endl;
    }
    // given relation
    vector<pair<string, string>> queryRelation(string _relation) {
        vector<pair<string, string>> facts;
        for(auto& subject: graph)
            for(auto& object: subject.second.relation[_relation])
                facts.push_back(make_pair(subject.first, object));
        return facts;
    }
    // given relation and subject
    vector<string> queryRelation(string _relation, string subject) {
        vector<string> facts;
        for(auto& object: graph[subject].relation[_relation])
            facts.push_back(object);
        return facts;
    }
};

class RuleBase {
    // each list<string> will be regard as a relationship chain
    unordered_map<string, vector<list<string>>> rules;
public:
    void insertRule(list<string> facts) {
        if(facts.size() < 2) {
            cout << "not a valid rule" << endl;
            return ;
        }
        if(rules.count(facts.front())) {
            cout << "rule exists" << endl;
            return ;
        }
        string name = facts.front();
        facts.pop_front();
        rules[name].push_back(facts);
    }
    
    // (note) if delete a rule, also delete all other rules depend on that
    void dropRule();
    vector<list<string>> getRule(string rule) {
        if(!rules.count(rule))
            return vector<list<string>>();
        return rules[rule];
    }
    void printRules() {
        for(auto& rule: rules)
            for(auto& ruleBody: rule.second) {
                cout << rule.first;
                for(auto& fact: ruleBody)
                    cout << "->" << fact;
                cout << endl;
            }
    }
};

class SRI {
    void parseStringInput();		// parse input string
    void parseStringOutput();		// parse output string
    void queryRuleHelper(vector<vector<string>>& ret, vector<string>& row, const list<string>& rule, list<string>::iterator index, string start) {
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
public:
    KnowledgeBase knowledgebase;
    RuleBase rulebase;
    // calling parseStringInput() to parse string, call function of drop, insert
    // in Base classes to execute query
    void executeQuery(string input);
    void load();			// load rules and facts
    void dump();			// dump rules and facts
    void insertRule(list<string> facts) {
        rulebase.insertRule(facts);
    }
    void dropRule();
    void printRule() {
        rulebase.printRules();
    }
    void insertFact(string relation, string subject, string object) {
        knowledgebase.insertFact(relation, subject, object);
    }
    void printGraph() {
        knowledgebase.printGraph();
    }
    void dropFact(string relation, string subject, string object) {
        knowledgebase.dropFact(relation, subject, object);
    }
    void queryRule(string _rule) {
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
};


int main(int argc, const char * argv[]) {
    SRI s;
    // insert facts
    s.insertFact("Father", "Mark", "Greg");
    s.insertFact("Father", "Mark", "Stanley");
    s.insertFact("Father", "John", "Mark");
    s.insertFact("Mother", "Marry", "Stanley");
    s.insertFact("Father", "Stanley", "Lucy");
    
    // drop facts
    s.dropFact("Mother", "Marry", "Stanley");
    
    // print facts
//    s.printGraph();
    
    // insert rules
    s.insertRule({"Grandfather", "Father", "Father"});
    s.insertRule({"Grandgrandfather", "Father", "Father", "Father"});
    
    // query rules
//    s.queryRule("Grandfather");
    s.queryRule("Grandgrandfather");
    
    return 0;
}
