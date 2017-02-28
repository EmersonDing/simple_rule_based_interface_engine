/*
 sri.cpp
 Group 9
 */

#include "sri.hpp"
vector<pair<string, string>> SRI::queryRuleHelper(Rule rule, string start, string end, unordered_set<string>& visited, string s, string e) {
    if(start == end)
        return {};
    if(visited.count(start))
        return vector<pair<string, string>>();
    vector<pair<string, string>> ret;
    bool isFirstEdge = false;
    visited.insert(start);
    unordered_set<string> dict;
    for(auto& edge: rule.ruleGraph[start]) {
        string relation = edge.first;
        vector<pair<string, string>> r;
        vector<pair<string, string>> _row;
        if(knowledgebase.knowledge_dict.count(relation)) {
            r = knowledgebase.queryRelation(relation, s, e);
        }
        else {
            r = queryRule(relation, s, e);
        }
        if(edge.second != end)
            for(auto& _r: r) {
                auto t = queryRuleHelper(rule, edge.second, end, visited, _r.second, e);
                for(auto& _t: t)
                    if(s == "") _t.first = _r.first;
                    else _t.first = s;
                _row.insert(_row.end(), t.begin(), t.end());
            }
        else
            _row = r;
        if(!isFirstEdge || !rule.isAnd) {   // if is OR
            isFirstEdge = true;
            for(auto& _r: _row)
                if(s == "")
                    dict.insert(_r.first + " " + _r.second);
                else
                    dict.insert(s + " " + _r.second);
        } else {
            unordered_set<string> dict_temp;
            for(auto& _r: _row) {
                string str;
                if(s == "")
                    str = _r.first + " " + _r.second;
                else
                    str = s + " " + _r.second;
                if(dict.count(str)) dict_temp.insert(str);
            }
            dict = dict_temp;
        }
    }
    for(auto& str: dict) {
        string str1 = str.substr(0, str.find(' ')),
        str2 = str.substr(str.find(' ')+1);
        if(e == "" || e == str2)
            ret.push_back({str1, str2});
    }
    visited.erase(start);
    return ret;
}


void SRI::insertRule(string name, pair<string, string> startEnd, bool isAnd, vector<pair<string, pair<string, string>>> params)
{
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

void SRI::dropRule(string rule)
{
    rulebase.dropRule(rule);
}

vector<pair<string, string>> SRI::queryRule(string _rule, string start, string end) {
    vector<pair<string, string>> ret;
    if(!knowledgebase.knowledge_dict.count(_rule)) {
        unordered_set<string> visited;
        Rule rule = rulebase.getRule(_rule);
        ret = queryRuleHelper(rule, rule.startEnd.first, rule.startEnd.second, visited, start, end);
    } else
        ret = knowledgebase.queryRelation(_rule, start, end);
    return ret;
}








void SRI::parseInput(string input)
{


    std::stringstream stream(input);

    std::string command;
    stream >> command;
    if(command == "LOAD")
    {
        std::string fileName;
        std::string factDefParts; //in case there is whitespace between params in definition of fact
        while(stream >> factDefParts)
        {
            fileName.append(factDefParts);
        }
    
        load(fileName);
    
    }
    else if(command == "DUMP")
    {
    
    
        std::string fileName;
        std::string factDefParts; //in case there is whitespace between params in definition of fact
        while(stream >> factDefParts)
        {
            fileName.append(factDefParts);
        }
    
    
        if(fileName != "")
            dump(fileName);
        else
            dump(); //default to out.sri
            
    }
    else if(command == "FACT")
    {
        std::string factDef;
        std::string factDefParts; //in case there is whitespace between params in definition of fact
        while(stream >> factDefParts)
        {
            factDef.append(factDefParts);
        }
        std::vector<std::string> factInfo = InputParser::tokenize(factDef); //tokenize with FACT call, only use string as a paramater

    
        insertFact(factInfo[0], factInfo[1], factInfo[2]);
    }
    else if(command == "RULE")
    {
        std::string ruleDef;
        std::string ruleDefParts; //in case there is whitespace between params in definition of fact
    
        std::string logicalRelation; //AND or OR
    
        while(stream >> ruleDefParts)
        {
            if(ruleDefParts == "AND" || ruleDefParts == "OR")
            {
                logicalRelation = ruleDefParts;
                continue;
            }
            ruleDef.append(ruleDefParts);
        }
    
        bool logOp;
        if(logicalRelation == "AND")
            logOp = true; //used for paramater isAND in insertRule()
        else if(logicalRelation == "OR")
            logOp = false;
        else
        {
            cout << "Invalid logical relation. Must be AND/OR. Rule was not stored." << endl;
            return;
        }
        
        parseAndInsertRule(ruleDef,logOp);
        
        }
    else if(command == "DROP")
    {
        std::string ruleOrFact;
        std::string factDefParts; //in case there is whitespace between params in definition of fact
        while(stream >> factDefParts)
        {
            ruleOrFact.append(factDefParts);
        }
        
        if(InputParser::isRule(ruleOrFact))
        {
            if(rulebase.isRule(ruleOrFact))
                dropRule(ruleOrFact);
            else
            {
                dropInferenceFacts(ruleOrFact); //this is used when deleting all facts declared from an inference, i.e GF facts declared after a Grandfather inference
            }
        }
        else
        {
            std::vector<std::string> factInfo = InputParser::tokenize(ruleOrFact);
            dropFact(factInfo[0], factInfo[1], factInfo[2]);
        }
    }
    
    else if(command == "INFERENCE")
    {
        std::string inferenceQuery;
        std::string queryParts; //in case there is whitespace between params in definition of fact
        while(stream >> queryParts)
        {
            inferenceQuery.append(queryParts);
        }
        
        
        std::vector<std::string> inferenceInfo = InputParser::tokenize(inferenceQuery); //tokenize with FACT call, only use string as a paramater
        pair<string, string> varNames; //used in printing the results of the query
        
        for(string& part : inferenceInfo)
        {
            //cout << part << endl;
            if(part[0] == '$')
            {
                if(part == inferenceInfo[1])
                    varNames.first.append(&part[1]);
                else
                    varNames.second.append(&part[1]);
                part = ""; //blank strings are considered parameters in queryRule, so adjust we these strings accordingly here
            }
        }
        
        auto queryResults = queryRule(inferenceInfo[0], inferenceInfo[1], inferenceInfo[2]);
        
        if(inferenceInfo.size() == 4) //declaring new facts based on result of inference
        {
            cout << "inserting fact based on query" << endl;
            for(auto& result: queryResults)
                insertFact( inferenceInfo[3], result.first, result.second);
        }
        else
            InputParser::printPair(queryResults, varNames); //only print if facts aren't being declared based on inference
        
       
        
    }
    else
    {
        cout << "Unknown command. All commands must be in all caps, and must be one of the following: LOAD, DUMP, FACT, RULE, INFERENCE, or DROP\n";
    }


}


void SRI::parseAndInsertRule(string ruleDef, bool logOp)
{
 
    unordered_map<string, pair<string, string>> factParams;
    std::vector<std::string> ruleInfo = InputParser::tokenize(ruleDef, factParams);//call with map as second arg, use overloaded version for parsing a rule
    
    vector<pair<string, pair<string, string>>> rulePredicates;
    string ruleName = ruleInfo[0];
    pair<string, string> ruleParams;
    ruleParams.first = factParams[ruleName].first; //insert only the var name X from $X
    ruleParams.second = factParams[ruleName].second;
    
    
    for(int i = 1; i < ruleInfo.size(); i++)
    {
        string factName = ruleInfo[i];
        pair<string, string> factPreds = factParams[factName];
        
        pair<string, pair<string, string>> factPredPair;
        factPredPair.first = factName;
        factPredPair.second = factPreds;
        
        rulePredicates.push_back(factPredPair);
        
    }
    

    
    insertRule(ruleName, ruleParams, logOp, rulePredicates);

}


void SRI::load(const string& path)
{
    std::ifstream file;
    file.open(path);
    if(!file.is_open())
    {
        std::cout << "Failed to load from file \'" << path << "\', consider checking the file name and/or extension." << std::endl;
        return;
    }
    
    std::string currentLine;
    while(std::getline(file, currentLine)) //read next line from file into string currentLine unil EOF
    {
        parseInput(currentLine);
        
    }
}

            

    

void SRI::dump(const string& path) //defaults to out.txt
{
   
    std::ofstream outfile(path);

    knowledgebase.writeToFile(outfile);
    rulebase.writeToFile(outfile);

    
    outfile.close();
}

void SRI::dropInferenceFacts(string facts)
{
    knowledgebase.dropInferenceFacts(facts);
}




