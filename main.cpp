#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <cstring>
#include <vector>
#include "Knight.h"
#include "Rabbit.h"
using namespace std;
void checkCommandLine(int argc, char* argv[]);
void createKnights();
void createRabbit();
char portnum[81];
// Message record
struct inputs
{
    char input[300];
};
std::vector<string> knightMessages;     //Vector of messages from knight file
std::vector<string> rabbitMessages;     //Vector of messages from rabbit file
std::vector<inputs> logMessages;        //Message struct of messages from knight & rabbit file to be sent to logger

int main(int argc, char** argv) {
    struct addrinfo *myinfo; // Address record
    int sockdesc;
    char hostname[81];
    char portnum[81];
    int connection;
    int value;

    checkCommandLine(argc, argv);
    //set log file name
    strcpy(hostname, argv[2]);
    //set port number
    strcpy(portnum, argv[4]);
    cout << hostname;
    cout << portnum;

    //validate rabbit & knight files
    createKnights();
    createRabbit();
    //Display messages from rabbit & knight files to user
    for(inputs msg : logMessages){
        string line;
        line = msg.input;
        std::cout << line << std::endl;
    }


    // Use AF_UNIX for unix pathnames instead
    // Use SOCK_DGRAM for UDP datagrams
    cout << "Before socket" << endl;
    sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockdesc < 0 )
    {
        cout << "Error creating socket" << endl;
        exit(0);
    }
    // Set up the address record
    cout << "Before getaddrinfo" << endl;
    if ( getaddrinfo(hostname, portnum, NULL, &myinfo) != 0 )
    {
        cout << "Error getting address" << endl;
        exit(0);
    }
    // Connect to the host
    cout << "Before connect" << endl;
    connection = connect(sockdesc, myinfo->ai_addr, myinfo->ai_addrlen);
    if ( connection < 0 )
    {
        cout << "Error in connect" << endl;
        exit(0);
    }
    cout << "Client connection = " << connection << endl;

    //Write all messages from knight & rabbit files to server / logger
    for(inputs msg : logMessages){
        // Send the message to the server
        write(sockdesc, (char*)&msg, sizeof(inputs));
    }
    // Close the socket
    close(sockdesc);
    return 0;
}
//Verify command line arguements
void checkCommandLine(int argc, char* argv[]){
    string bleh;
    //Verifying command line arguements
    int flag1 = 0; //set to 1 if -l found
    int flag2 = 0; //set to 1 if -p found
    //Loop through command line arguements. Check for -l -p
    for(int i = 0; i < argc; i++){
        if(strcmp (argv[i], "-s") == 0){
            flag1 = 1;
            if(strcmp (argv[i+1], "-p") == 0){
                cout << "Error: Log server was not listed.\n";
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
        cout << "Error: -s arguement missing.\n";
        exit(0);
    }
    if(flag2 == 0) {
        cout << "Error: -p arguement missing.\n";
        exit(0);
    }
}
//Checks formatting and values of rabbit file stores messages to send to log
void createRabbit(){
    Rabbit newRabbit;
    newRabbit.rabbitFileName = "rabbitfile";
    //validate format of key:value for rabbitfile
    int val1 = newRabbit.openRabbitFile();
    //validate value for rabbitfile
    int val2 = newRabbit.validateRabbit();

    //All messages to be sent to logged from knight are stored in string vector
    rabbitMessages = newRabbit.queOfMessages;

    //Create struct for each message from rabbit and store in logMessages to communicate with server
    for(string message : rabbitMessages){
        inputs tempMsg;
        strcpy(tempMsg.input, message.c_str());
        logMessages.push_back(tempMsg);
    }
    //push message that indicates end of the log for knight & rabbit
    inputs tempMsg;
    string line = "End log";
    strcpy(tempMsg.input, line.c_str());
    logMessages.push_back(tempMsg);

}
//Checks formatting and values of knight file stores messages to send to log
void createKnights(){
    //Vector of knights created
    std::vector<Knight> listOfKnights;
    Knight newKnight;
    newKnight.knightFileName = "knightfile";


    //validate count matches with amount of knights. Store log messages in que
    newKnight.validateAmountOfKnights();
    //validate format of key:value for knightFile
    newKnight.openKnightFile();
    //create list of knights and validate their properties
    listOfKnights = newKnight.createKnight();
    //All messages to be sent to logged from knight are stored in string vector
    knightMessages = newKnight.queOfMessages;


    //Create struct for each message from knight and store in logMessages to communicate with server
    for(string message : knightMessages){
        inputs tempMsg;
        strcpy(tempMsg.input, message.c_str());
        logMessages.push_back(tempMsg);
    }
}