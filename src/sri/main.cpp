/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <cstring>
#include "sri.hpp"
#include "TCPServerSocket.h"



using namespace std;


int main() {
    SRI s;
    TCPServerSocket server(9999);
    TCPSocket * client = server.getConnection();
    cout << "Recieved Connection" << "\n";
    char buffer[8192];
    while (true) {
        client->readFromSocket(buffer, 65536);
        string input(buffer);
        cout << "Recieved command: " << input << "\n";

        if (input == "q" || input == "Q") break;
            try
            {
                memset(buffer, 0, 8192);
                string ret = s.parseInput(input);
                cout << "Returned: " << ret << "\n";
                if (ret == "") ret = "\n";
                strcpy(buffer, ret.c_str());
                client->writeToSocket(buffer, strlen(buffer));
            }
            catch(...)
            {
                cerr << "Error parsing input\n";
            }
    }
    delete client;
    
    return 0;
}
