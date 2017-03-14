/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <cstring>
#include "TCPSocket.h"


using namespace std;


int main() {
    char addr[128] = "127.0.0.1";
    TCPSocket client(addr, 9999);
    
    char buffer[8192];
    string input;
    
    while (input != "q" && input != "Q") {
        input = "";
        while (input == "") {
            printf("Enter an SRI comand, or (Q)uit : ");
            getline(cin, input);
        }
        int ret = client.writeToSocket(input.c_str(), input.length());
        //cout << "Wrote " << ret << " bytes" << "\n";
        client.readFromSocket(buffer, 65536);
        if (buffer[0] != '\n') cout << buffer;
    }
    
    return 0;
}
