/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

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

    
    while(input != "q" && input != "Q") //poll input until user is ready to quit
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
