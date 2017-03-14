/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <cstring>
#include <thread>
#include "sri.hpp"
#include "TCPServerSocket.h"



using namespace std;

void handleConnection(TCPSocket *client) {
    cout << "Started client thread\n";
    SRI s;
    char buffer[8192];
    
    while (true) {
        client->readFromSocket(buffer, 65536);
        string input(buffer);
        memset(buffer, 0, 8192);
        string ret;

        if (input == "q" || input == "Q") break;
            try
            {
                ret = s.parseInput(input);
                if (ret == "") ret = "\n";
            }
            catch(...)
            {
                ret = "Error parsing input\n";
            }
        strcpy(buffer, ret.c_str());
        client->writeToSocket(buffer, strlen(buffer));
    }
    delete client;
    cout << "Ended client thread\n";
}

void call_from_thread(string s) {
    cout << s << "\n";
}

int main() {
    bool running = true;
    TCPServerSocket server(9999);
    while (running) {
        TCPSocket * client = server.getConnection();
        cout << "Recieved Connection" << "\n";
        thread(handleConnection, client).detach();
    }
    
    return 0;
}
