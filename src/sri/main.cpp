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
#include "sri.hpp"



using namespace std;


int main(int argc, const char * argv[]) {
    SRI s;
    
    
    string input;
    printf("Enter an SRI comand, or (Q)uit : ");
    getline(cin, input);

    
    while(input != "q" && input != "Q")
    {
        try
        {
            s.parseInput(input);
        }
        catch(...)
        {
            cerr << "Input was invalid\n";
        }
        printf("Enter an SRI comand, or (Q)uit : ");
        getline(cin, input);
        
    }
    

    
    return 0;
}
