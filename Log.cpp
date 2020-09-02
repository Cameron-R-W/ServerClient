//
// Created by Camtheconqueror on 4/19/2020.
//

#include "Log.h"

//
// Created by Camtheconqueror on 2/19/2020.
//

#include <fstream>
#include "Log.h"
//sets log file name
void Log::setLogName(string logName)
{
    logFileName = logName;
}

//returns log file name
string Log::getLogName()
{
    string logName;
    logName = logFileName;
    return logName;
}

//Opens log with timestamp begin timestamp
void Log::openLogFile()
{
    string timeStamp = getTime();
    string logName = getLogName();
    std::ofstream logFile(logName, std::ios_base::app);
    logFile << "\n" << timeStamp;
    logFile << "Begin Log";
    timeStamp = getTime();
    logFile << "\n" << timeStamp << "\n";
    logFile.close();
}

//close log file
void Log::closeLogFile()
{
    string timeStamp = getTime();
    string logName = getLogName();
    std::ofstream logFile(logName, std::ios_base::app);
    logFile << "\n" << timeStamp;
    logFile << "End Log";
    timeStamp = getTime();
    logFile << "\n" << timeStamp;
    logFile.close();
}

//returns time in a string "timeStamp"
string Log::getTime()
{
    string timeStamp;
    time_t curr_time;
    curr_time = time(NULL);
    char *tm = ctime(&curr_time);
    timeStamp = tm;
    return timeStamp;
}
//Opens log file and stamps "Begin combat" with time stamp to log file
void Log::beginLog()
{
    string logName = getLogName();
    string timeStamp = getTime();
    std::ofstream logFile(logName, std::ios_base::app);
    logFile << "\n" << timeStamp;
    logFile << "Begin Log";
    timeStamp = getTime();
    logFile << "\n" << timeStamp << "\n";
}
//Closes log file and stamps "End combat" with the time stamp to log file
void Log::endLog()
{
    string logName = getLogName();
    string timeStamp = getTime();
    std::ofstream logFile(logName, std::ios_base::app);
    logFile << "\n" << timeStamp;
    logFile << "End log";
    timeStamp = getTime();
    logFile << "\n" << timeStamp << "\n";
    logFile.close();
}
//Writes a string to the log file
void Log::writeToLog(string m)
{
    string logName = getLogName();
    std::ofstream logFile(logName, std::ios_base::app);
    logFile << m;
    logFile << "\n";
}