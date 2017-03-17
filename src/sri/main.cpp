/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <thread>
#include "sri.hpp"
#include "TCPServerSocket.h"



using namespace std;

//used for the dump command
void sendFile(TCPSocket *client, SRI *s) {
    char fname[32];
    //generate a unique name for a temp file
    sprintf(fname, "~tmp%ld", time(NULL));
    //dump into that file
    s->dump(string(fname));
    //send the file to the client
    ifstream file;
    file.open(fname);
    string line;
    while(getline(file, line)) {
        //send the line to the client
        client->writeToSocket(line.c_str(), line.length());
    }
    file.close(); //close and delete the temp file
    remove(fname);
    line = "\n"; //end the file
    client->writeToSocket(line.c_str(), line.length());
}

//handle a client connection
void handleConnection(TCPSocket *client) {
    cout << "Started client thread\n";
    SRI s; //create a new SRI for this client
    char buffer[8192]; //buffer for sending data
    
    while (true) { //loop until the user types 'q'
        memset(buffer, 0, 8192); //zero the buffer
        int recv = client->readFromSocket(buffer, 65536); //read data
        if (recv < 1) break; //break if the user improperly disconnected
        string input(buffer); //convert it to a string
        string ret; //string that is returned to the client
        
        //break if the user requested a disconnect
        if (input == "q" || input == "Q") break;
            try
            {
                if (input.substr(0,5) == "DUMP ") {
                    sendFile(client, &s);
                    continue;
                }
                ret = s.parseInput(input); //the SRI's parse function
                if (ret == "") ret = "\n"; //return \n for no data
            }
            catch(...)
            {
                ret = "Error parsing input\n"; //malformed query
            }
        //strcpy(buffer, ret.c_str()); //copy the return string into the output buffer
        client->writeToSocket(ret.c_str(), ret.length()); //send it off
    }
    delete client; //close the socket when the client disconnects
    cout << "Ended client thread\n";
}

int main() {
    TCPServerSocket server(9999); //start a server
    while (true) { //loop forever waiting for connections
        TCPSocket * client = server.getConnection(); //get a connection
        cout << "Recieved Connection" << "\n";
        thread(handleConnection, client).detach(); //spawn a thread to handle it
    }
    
    return 0;
}
