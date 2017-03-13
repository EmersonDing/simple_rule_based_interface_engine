/*
 InputParser.hpp
 Group 9
 This class is intended to be used only as a utility class, since all of its methods are static. It is used to
 simplify code in SRI for parsing strings and returning the input in a format that can be used by the rule or
 knowledge base
*/

#ifndef InputParser_hpp
#define InputParser_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>
#include <cstring>

using namespace std;



class InputParser
{

    
public:
    InputParser();
    
    //void parseInput(string input);
    static string printPair(vector<pair<string, string>> v, pair<string, string> varNames);
    
    static vector<string> tokenize(string& s, unordered_map<string, pair<string, string>>& factParams); //overloaded to parse input for a RULE 
    static vector<string> tokenize(string& s); //overloaded to parse input for a FACT
    static bool isRule(string FactOrRule);
};


#endif /* InputParser_hpp */
