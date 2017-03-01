/*
 knowledge.hpp
 Group 9
 This class is used ot model a KnowledgeBase. It will contain all the facts used by the SRI. Facts are stored as a 
 graph, where each node consists of the name of a parent node's relation and a set of the names it is related to by
 this relation.
 */

#ifndef knowledge_hpp
#define knowledge_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>
using namespace std;
#endif /* knowledge_hpp */


class FactNode {
public:
    // save relations of a people.
    // e.g. {{"Father", {Peter"}}, {"Brother", {"John"}}} in Mark's relation
    // means Father(Mark,Peter), Brother(Mark,John)
    unordered_map<string, unordered_set<string>> relation;
};

class KnowledgeBase {
public:
    unordered_map<string, int> knowledge_dict;  // store name of all facts
    unordered_map<string, FactNode> graph;		// store people and their relations

    
  
    void insertFact(string relation, string subject, string object);
    void dropFact(string relation, string subject, string object);
    void printGraph();
    vector<pair<string, string>> queryRelation(string _relation, string subject = "", string _object = "");
    
    void writeToFile(std::ofstream& outfile);
    
    void dropInferenceFacts(string facts); //used to delete facts created as the result of an inference
};
