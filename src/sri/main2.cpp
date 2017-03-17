/*
 main.cpp
 Group 9
 This program will keep polling for input from the user and pass this input to its SRI to handle until the user 
 decides to quit. The user MUST dump the contents of the SRI in order for the rules and facts from their session to be 
 saved
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "TCPSocket.h"


using namespace std;

char buffer[8192]; //buffer for reading data

//called when the user types LOAD
void sendFile(TCPSocket *client, const char *fname) {
    ifstream file;
    file.open(fname); //open the file
    if (!file.is_open()) {
        std::cout << "Failed to load from file \'" << fname << "\', consider checking the file name and/or extension.\n";
        return;
    }

    string line;
    while(getline(file, line)) {
        //don't send a blank line
        if (line == "") continue;
        //send a line of the file like a normal command
        client->writeToSocket(line.c_str(), line.length());
        //wait for the server to acknowledge
        client->readFromSocket(buffer, 65536);
    }
    file.close();
}

//called when the user types dump
void recieveFile(TCPSocket *client, const char *fname) {
    ofstream file(fname); //open file for writing
    buffer[0] = 0;

    client->readFromSocket(buffer, 65536);
    while (buffer[0] != '\n') { //loop until server is done
        file << buffer << "\n";
        client->readFromSocket(buffer, 65536);
    }

    file.close(); //close the file
}

int main() {
    TCPSocket *client; //pointer to the socket

    while (true) { //loop, allowing the client to connect to different servers
        while (true) { //loop until the user provides a valid address
            char addr[128];
            cout << "Enter the server IP, or (Q)uit: ";
            cin.getline(addr, 128);

            //exit if the user typed q
            if (addr[0] == 'q' || addr[0] == 'Q') return 0;
            try {
                client = new TCPSocket(addr, 9999); //attempt to connect
                break; //leave the loop if successful
            }
            catch (...) {
                //failed, try again
                cout << "Failed to connect to " << addr <<"\n";
            }
        }
        
        string input; //the user's input
        
        while (input != "q" && input != "Q") { //disconnect if the user typed q
            input = "";
            while (input == "") { //don't try to send an empty string
                printf("Enter an SRI comand, or (Q)uit: ");
                getline(cin, input); //get user input
            }

            //clientside handling of load and dump
            string cmd = input.substr(0,5);
            if (cmd == "LOAD ") {
                sendFile(client, input.substr(5).c_str());
                continue;
            }
            if (cmd == "DUMP ") {
                //tell the server we want a dump
                client->writeToSocket(input.c_str(), input.length());
                //handle the response
                recieveFile(client, input.substr(5).c_str());
                continue;
            }

            //send the query to the server
            client->writeToSocket(input.c_str(), input.length());
            //wait for a response
            int recv = client->readFromSocket(buffer, 65536);
            if (recv < 1) { //break on connection loss
                cout << "Lost connection to server\n";
                break;
            }
            //output nothing if the server returned \n
            if (buffer[0] != '\n') cout << buffer;
        }
        delete client; //close the socket
    }
    
    return 0;
}
