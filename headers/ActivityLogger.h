#ifndef ACTIVITYLOGGER_H
#define ACTIVITYLOGGER_H
#include<cstdlib>
#include<iostream>
#include<string>
#include<list>
#include<cstdio>
using namespace std;
class Logger{
    private:
    list<string> logEntries;
    int detectionLevel;
    string logFilePath;
    public:
    //constructors 
    Logger(const list<string>& logEntries,const string& logFilePath):logEntries(logEntries),detectionLevel(0),logFilePath(logFilePath){}
    Logger():logEntries(),detectionLevel(0),logFilePath(""){}
    
    Logger(const Logger& obj):logEntries(obj.logEntries),detectionLevel(obj.detectionLevel),logFilePath(obj.logFilePath){}
    //setters
    
    
    void setLogEntries(const list<string>& logEntries);
    void setLogFilePath(const string& logFilePath);
    void setDetectionLevel(int level);      

    //getters
    list<string> getLogEntries()const;
    string getLogFilePath()const;
    int getDetectionLevel()const;
//methods 
void log(const string& event);
void showlogs();//print logs 
void clearLogs();//clear logs from memory and file
void incrementDetectionLevel();//increment detection level when a threat is detected
void exportLogs(string targetPath = "");//export logs to a specified location
};
    
#endif
