//
//  InputParser.cpp
//  Group 9
//
//

#include "InputParser.hpp"


InputParser::InputParser()
{

}

bool InputParser::isRule(string factOrRule)
{
    char nextChar;
    std::string st;
    unsigned int i = 0;
    
    while(i < factOrRule.length())
    {
        nextChar = factOrRule[i++];
        if(nextChar == '(' )
            return false; //if there are parantheses, this is a fact, not a rule
        
        
    }
    //if no ( were found, user is trying to drop a rule.
    return true;
}

std::vector<std::string> InputParser::tokenize(std::string& s, unordered_map<string, pair<string, string>>& factParams) //this method is used for tokenizing a string for inserting a rule
{
    std::vector<std::string> parsedString;
    
    char nextChar;
    std::string st;
    unsigned int i = 0;
    int j = 0; //keeps track of which word was just added so we can link predicates to variables, i.e Father to $X, $Y
    
    while(i < s.length())
    {
        nextChar = s[i++];
        if(nextChar == ' ' )
            continue; //ignore whitespace
        
        else if( nextChar == '(') //when parsing rules, parantheses are considered in a different way than when parsing facts
        {
            if (!st.length()) //do not add blank strings
                continue;
            parsedString.push_back(st);
            j++;
            st.erase(); //reset st so we can get next parsed element
            
            
            
            pair<string, string> currFactParams;
            while(nextChar != ')')
            {
                nextChar = s[i++];
                while(nextChar != ',' && nextChar != ')')
                {
                    if(nextChar != ' ')
                        st += nextChar;
                    nextChar = s[i++];
                    
                }
                if(currFactParams.first == "")
                    currFactParams.first = st[1];
                else
                    currFactParams.second = st[1];//extract only the Varibale, ignore the $ internally
                st.erase();
                
            }
            
            
            factParams[parsedString[j-1]] = currFactParams; //previous element has the factParams tied to them
            
        }
        
        
        if(nextChar == ')' || nextChar == ':' || nextChar == '-')
        {
            st.erase(); //reset st so we can get next parsed element
            continue;
        }
        st += nextChar;
        
        
    }
    
    return parsedString;
}


std::vector<std::string> InputParser::tokenize(std::string& s) //when only given string, this is used for tokenizing a FACT
{
    std::vector<std::string> parsedString;
    
    char nextChar;
    std::string st;
    unsigned int i = 0;
    
    while(i < s.length())
    {
        nextChar = s[i++];
        if(nextChar == ' ' )
            continue; //ignore whitespace
        
        
        
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
    if (st.length()) //do not add blank strings. This final push_back to the parsedString vector is for when the user wants to add new facts based on the results of a query
        parsedString.push_back(st);
    
    
    return parsedString;
}


string InputParser::printPair(vector<pair<string, string>> v, std::pair<string, string> varNames)
{
    string ret;
    //if the query was filtered, update output accordingly. We know query is filtered when varName is blank
    if(varNames.first != "")
        varNames.first.append(":");
    if(varNames.second != "")
        varNames.second.append(":");
    
    for(auto r: v)
    {
        if(varNames.first[1] != ':')
            r.first = "";
        if(varNames.second[1] != ':')
            r.second = "";
        ret += r.first;
        ret += "\t";
        ret += r.second;
        ret += "\n";
        //cout << varNames.first  << r.first << '\t' << varNames.second  << r.second << endl;
    }
    return ret;
}
