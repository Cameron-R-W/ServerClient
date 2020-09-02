//
// Created by Camtheconqueror on 5/3/2020.
//

#ifndef HW7SERVER_LOG_H
#define HW7SERVER_LOG_H
#include <string>
using namespace std;

class Log {
public:
    string logFileName;
    //Retrieve name of log file
    string getLogName();
    //Creates log file
    void openLogFile();
    //Returns time stamp in a string
    string getTime();
    //Set name of log file
    void setLogName(string logName);
    //Close log file
    void closeLogFile();
    //end log file
    void endLog();
    //Begin log file *file name has to be logfile
    void beginLog();
    //Write a string to log file *file name has to be logfile
    void writeToLog(string m);
};


#endif //HW7SERVER_LOG_H
