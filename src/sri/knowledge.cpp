/*
 knowledge.hpp
 Group 9
 */

#include "knowledge.hpp"
void KnowledgeBase::insertFact(string relation, string subject, string object) {
    // if relation already exists
    if(graph.count(subject) && graph[subject].relation.count(object)) {
        cout << "relationship already exist." << endl;
        return ;
    }
    graph[subject].relation[relation].insert(object);
    ++knowledge_dict[relation];
}

void KnowledgeBase::dropFact(string relation, string subject, string object) {
    if(!graph.count(subject) || !graph[subject].relation.count(relation) || !graph[subject].relation[relation].count(object)) {
        cout << "no such relationship." << endl;
        return ;
    }
    graph[subject].relation[relation].erase(object);
    if(--knowledge_dict[relation] == 0)
        knowledge_dict.erase(relation);
}

void KnowledgeBase::printGraph() {
    for(auto& subject: graph)
        for(auto& relation: subject.second.relation)
            for(auto& object: relation.second)
                cout << relation.first << ": " << subject.first << "," << object << endl;
}

vector<pair<string, string>> KnowledgeBase::queryRelation(string _relation, string _subject, string _object)
{
    vector<pair<string, string>> facts;
    if(_subject == "")
        for(auto& subject: graph)
            for(auto& object: subject.second.relation[_relation]) {
                if(_object == "" || _object == object)
                    facts.push_back(make_pair(subject.first, object));
            }
    else
        for(auto& object: graph[_subject].relation[_relation])
            if(_object == "" || _object == object)
                facts.push_back(make_pair(_subject, object));
    return facts;

}

void KnowledgeBase::writeToFile(std::ofstream& outfile)
{
    //write facts to file in the format specified by the project description
    for(auto& subject: graph)
        for(auto& relation: subject.second.relation)
            for(auto& object: relation.second)
                outfile << "FACT " << relation.first << "(" << subject.first << "," << object << ")" << endl;
}

void KnowledgeBase::dropInferenceFacts(string relation)
{
    vector<pair<string, string>> factsToDelete = queryRelation(relation);
    for(pair<string,string> fact : factsToDelete)
    {
        dropFact(relation, fact.first, fact.second);
    }
    

    
    
}

