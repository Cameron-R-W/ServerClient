#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "Log.h"

using namespace std;
void checkCommandLine(int argc, char* argv[]);
struct clientMessage{
    char message[300];
};
//Layout for connecting Server & Client taken from Professor Harrison demo on Einstein
int main(int argc, char** argv ) {
    char portnum[81];
    string fileName;
    int sockdesc;
    struct addrinfo *myinfo;
    clientMessage m;
    int connection;
    int value;

    // Create the socket with domain, type, protocol as
    //    internet, stream, default
    sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockdesc < 0 )
    {
        cout << "Error creating socket" << endl;
        exit(0);
    }
    //Verify command line arguements
    checkCommandLine(argc, argv);
    //set log file name
    fileName = argv[2];
    //set port number
    strcpy(portnum, argv[4]);
    // Set up the address record
    if ( getaddrinfo("127.0.0.1", portnum, NULL, &myinfo) != 0 )
    {
        cout << "Error getting address" << endl;
        exit(0);
    }
    // Bind the socket to an address
    if (bind(sockdesc, myinfo->ai_addr, myinfo->ai_addrlen) < 0 )
    {
        cout << "Error binding to socket" << endl;
        exit(0);
    }
    // Now listen to the socket
    if ( listen(sockdesc, 1) < 0 )
    {
        cout << "Error in listen" << endl;
        exit(0);
    }
    for(;;)
    {
        cout << "Calling accept" << endl;
        // Accept a connect, check the returned descriptor
        connection = accept(sockdesc, NULL, NULL);
        if ( connection < 0 )
        {
            cout << "Error in accept" << endl;
            exit(0);
        }
        else
        {
            //Initialize log and set the log file name
            Log log;
            log.logFileName = fileName;
            string line;
            //Opens log file with time stamp
            log.beginLog();
            //Keep reading messages from client until last message is sent
            //Write those messages to the logfile
            while(line != "End log"){
                value = read(connection, (char*)&m, sizeof(clientMessage));
                line = m.message;
                log.writeToLog(line);
            }
            //Closes log file with time stamp
            log.endLog();
            // Then quit
            break;
        }

    } // for

    // Close the connection
    close(connection);
    return 0;
}
//Verify command line arguements
void checkCommandLine(int argc, char* argv[]){
    //Verifying command line arguements
    int flag1 = 0; //set to 1 if -l found
    int flag2 = 0; //set to 1 if -p found
    //Loop through command line arguements. Check for -l -p
    for(int i = 0; i < argc; i++){
        if(strcmp (argv[i], "-l") == 0){
            flag1 = 1;
            if(strcmp (argv[i+1], "-p") == 0){
                cout << "Error: Log file was not listed.\n";
                exit(0);
            }
        }
        if(strcmp (argv[i], "-p") == 0){
            flag2 = 1;
            if(argc < 5){
                cout << "Error: Port number not listed.";
                exit(0);
            }
        }
    }
    if(flag1 == 0) {
        cout << "Error: -l arguement missing.\n";
        exit(0);
    }
    if(flag2 == 0) {
        cout << "Error: -p arguement missing.\n";
        exit(0);
    }
}