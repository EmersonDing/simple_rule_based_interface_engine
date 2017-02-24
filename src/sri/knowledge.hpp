//
//  knowledge.hpp
//  sri
//
//  Created by Emerson on 2/15/17.
//  Copyright © 2017 Emerson. All rights reserved.
//

#ifndef knowledge_hpp
#define knowledge_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;
#endif /* knowledge_hpp */


class FactNode {
public:
    // all relations of a people
    // e.g. {{"Father", {Peter"}}, {"Brother", {"John"}}}
    // means Father(Mark,Peter), Brother(Mark,John)
    unordered_map<string, unordered_set<string>> relation;
};

class KnowledgeBase {
public:
    unordered_map<string, FactNode> graph;		// store people and their relations
    void insertFact(string relation, string subject, string object);
    void dropFact(string relation, string subject, string object);
    void printGraph();
    vector<pair<string, string>> queryRelation(string _relation, string subject = "");
};
