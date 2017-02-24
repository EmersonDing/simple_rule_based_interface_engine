//
//  knowledge.cpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#include "knowledge.hpp"
void KnowledgeBase::insertFact(string relation, string subject, string object) {
    // if relation already exists
    if(graph.count(subject) && graph[subject].relation.count(object)) {
        cout << "relationship already exist." << endl;
        return ;
    }
    graph[subject].relation[relation].insert(object);
}
void KnowledgeBase::dropFact(string relation, string subject, string object) {
    if(!graph.count(subject) || !graph[subject].relation.count(relation) || !graph[subject].relation[relation].count(object)) {
        cout << "no such relationship." << endl;
        return ;
    }
    graph[subject].relation[relation].erase(object);
}
void KnowledgeBase::printGraph() {
    for(auto& subject: graph)
        for(auto& relation: subject.second.relation)
            for(auto& object: relation.second)
                cout << relation.first << ": " << subject.first << "," << object << endl;
}

vector<pair<string, string>> KnowledgeBase::queryRelation(string _relation, string subject) {
    vector<pair<string, string>> facts;
    if(subject == "")
        for(auto& subject: graph)
            for(auto& object: subject.second.relation[_relation])
                facts.push_back(make_pair(subject.first, object));
    else
        for(auto& object: graph[subject].relation[_relation])
            facts.push_back(make_pair(subject, object));
    return facts;
}