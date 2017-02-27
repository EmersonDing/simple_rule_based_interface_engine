//
//  InputParser.hpp
//  SRI
//
//

#ifndef InputParser_hpp
#define InputParser_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>

using namespace std;



class InputParser
{

    
public:
    InputParser();
    
    //void parseInput(string input);
    static void printPair(vector<pair<string, string>> v, pair<string, string> varNames);
    
    static vector<string> tokenize(string& s, unordered_map<string, pair<string, string>>& factParams);
    static vector<string> tokenize(string& s);
    static bool isRule(string FactOrRule);
};


#endif /* InputParser_hpp */
