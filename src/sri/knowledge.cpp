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
    graph[subject].relation[relation].push_back(object);
}
void KnowledgeBase::dropFact(string relation, string subject, string object) {
   /* if(!graph.count(subject) || !graph[subject].relation.count(relation) || !graph[subject].relation[relation].count(object)) {
        cout << "no such relationship." << endl;
        return ;
    }
    graph[subject].relation[relation].erase(object);*/
}
void KnowledgeBase::printGraph() {
    for(auto& subject: graph)
        for(auto& relation: subject.second.relation)
            for(auto& object: relation.second)
                cout << relation.first << ": " << subject.first << "," << object << endl;
}
// given relation
vector<pair<string, string>> KnowledgeBase::queryRelation(string _relation) {
    vector<pair<string, string>> facts;
    for(auto& subject: graph)
        for(auto& object: subject.second.relation[_relation])
            facts.push_back(make_pair(subject.first, object));
    return facts;
}
// given relation and subject
vector<string> KnowledgeBase::queryRelation(string _relation, string subject) {
    vector<string> facts;
    for(auto& object: graph[subject].relation[_relation])
        facts.push_back(object);
    return facts;
}

void KnowledgeBase::writeToFile(std::ofstream& outfile)
{
    for(auto& subject: graph)
        for(auto& relation: subject.second.relation)
            for(auto& object: relation.second)
                outfile << "FACT " << relation.first << "(" << subject.first << "," << object << ")" << endl;
}

bool KnowledgeBase::isFact(string relation, string subject, string object)
{
    vector<string> relations = graph[subject].relation[relation];
    for(string obj :relations)
    {
        if(obj == object)
            return true;
    }
    return false;
}


