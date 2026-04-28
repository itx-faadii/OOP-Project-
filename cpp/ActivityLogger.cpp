#include "../headers/ActivityLogger.h"
#include <unistd.h>
//setters
void  Logger::setLogEntries(const list<string>& logEntries){
    this->logEntries=logEntries;
}
void Logger::setLogFilePath(const string& logFilePath){
    this->logFilePath=logFilePath;
}
void Logger::setDetectionLevel(int level){
    this->detectionLevel=level;
}
//getters
list<string> Logger::getLogEntries()const{
    return this->logEntries;
}
string Logger::getLogFilePath()const{
    return this->logFilePath;
}

int Logger::getDetectionLevel()const{
    return this->detectionLevel;
}
//methods 
void Logger::log(const  string& event) {
    // Agar path khali hai to pehli baar set karwa lo
    if (logFilePath.empty()) {
        std::cout << "[!] Log file path not set. Enter path or press Enter for default: ";
        std::getline(std::cin, logFilePath);

        if (logFilePath.empty()) {
            #ifdef _WIN32
            //default path setting 
                logFilePath = "..\\logs\\activity.log";
            #else
                logFilePath = "../logs/activity.log";
            #endif
            std::cout << "[!] Default path set to: " << logFilePath << std::endl;
        }
    }

    //wrintg to the logEntries list and also writing to the file
    logEntries.push_back(event);

    string command;
    #ifdef _WIN32
        // command i learnt from google 
        command = "echo " + event + " >> \"" + logFilePath + "\"";
        _pclose(_popen(command.c_str(), "w"));
    #else
    //linux command for writing to file
        command = "echo \"" + event + "\" >> \"" + logFilePath + "\"";
        pclose(popen(command.c_str(), "w"));
    #endif
}
void Logger::showlogs() {
//check file path first ,ogic 
    if (logFilePath.empty()) {
      std::cout<< "[!] No log path found. Enter path to read logs (or press Enter for default): ";
        std::getline(std::  cin, logFilePath);
//deafult path setting if user do not provide any path
        if (logFilePath.empty()) {
            #ifdef _WIN32
                logFilePath = "..\\logs\\activity.log";
            #else
                logFilePath = "../logs/activity.log";
            #endif
        }
    }
//cpmmand setting and usage 
    string command;
    #ifdef _WIN32
        command = "type \"" + logFilePath + "\"";
    #else
        command = "cat \"" + logFilePath + "\"";
    #endif

    // Pipe logic used to print on the screen we could also use sleep to dealy it 
    #ifdef _WIN32
        FILE* pipe = _popen(command.c_str(), "r");
    #else
        FILE* pipe = popen(command.c_str(), "r");
    #endif

    if (!pipe) {
        std::cout << "[ERROR] Could not open logs at: " << logFilePath << std::endl;
        return;
    }
//the finction to pritn a file as we print files using c old style 
    char buffer[256];
    std::cout << "\n========== REAL-TIME SYSTEM LOGS ==========\n";
    
    // fgets logic of c old styel thath i learnt in 1 smester 
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        std::cout << buffer;
        std::cout.flush(); // Real-time display ke liye flush
    }   

    #ifdef _WIN32
    //pipe shoud also bne closed as file is clodes affetr usagw 
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif
    
    std::cout << "===========================================\n";
}

void Logger::exportLogs(string targetPath) {
    // if target path is not given then dektop path will be seted 
    if (targetPath.empty()) {
        #ifdef _WIN32
            // Windows mein %USERPROFILE%\Desktop each  PC has this  coomand google sy seacrh ki ha 
            targetPath = "..\\logs\\Activity_Backup.log";
        #else
            // Linux mein ~/Desktop ya /tmp/ standard hai command taken from google
            targetPath = "../logs/Activity_Backup.log";
        #endif
        
        std::cout << "[INFO] No path provided. Exporting to Desktop by default.\n";
    }

    
    // Agar logFilePath khali hai, to iska matlab abhi tak kuch log hi nahi hua
    if (logFilePath.empty()) {
        #ifdef _WIN32
            logFilePath = "..\\logs\\activity.log";
        #else
            logFilePath = "../logs/activity.log";
        #endif
        std::cout << "[!] Source log file was not set. Checking default location...\n";
    }

    string command;
    #ifdef _WIN32
        // cmd /c taake %USERPROFILE% jaise variables sahi se resolve hon
        command = "cmd /c copy \"" + logFilePath + "\" \"" + targetPath + "\"";
    #else
        command = "cp -i \"" + logFilePath + "\" \"" + targetPath + "\"";
    #endif

    //  System dependent execution taake Overwrite (Y/N) ka option milay sysytem hi hande kr ly ga us lye system ki command use kr di 
    system(command.c_str());

    std::cout << "[SUCCESS] Process finished. Check: " << targetPath << std::endl;
}
void Logger::clearLogs() {
    // defaukt path cheking logic
    if (logFilePath.empty()) {
        #ifdef _WIN32
            logFilePath = "..\\logs\\activity.log";
        #else
            logFilePath = "../logs/activity.log";
        #endif
    }

    //  1. Check if file exists at the path (if not, prompt user for manual path) user ki choce 
    string checkCmd;
    #ifdef _WIN32
        checkCmd = "if exist \"" + logFilePath + "\" (exit 0) else (exit 1)";
    #else
        checkCmd = "[ -f \"" + logFilePath + "\" ]";
    #endif

    // If file not found error printing logic 
    if (system(checkCmd.c_str()) != 0) {
        cout << "[!] Log file not found at default. Enter path to clear: ";
        getline(cin, logFilePath);

        if (system(checkCmd.c_str()) != 0) {
            cout << "[ERROR] Invalid path. Clear operation failed.\n";
            logFilePath = ""; 
            return;
        }
    }

    // Visual feedback using flush and delays  to make attarctieve 
    cout << "[SYSTEM] Wiping logs";
    cout.flush();
    for(int i = 0; i < 3; i++) {
        #ifdef _WIN32
        _sleep(700);
        #else
            u_sleep(700000);
        #endif
        cout << ".";
        cout.flush();
    }

    //  Clear memory and perform silent deletion  memory clear to prevent memory leaks 
    logEntries.clear();

    string delCmd;
    #ifdef _WIN32
    // command delete from google 
        delCmd = "del /f /q \"" + logFilePath + "\"";
    #else
        delCmd = "rm -f \"" + logFilePath + "\"";
    #endif
// command execution for deleting file
    system(delCmd.c_str());

    cout << "\n[SUCCESS] Memory cleared and log file deleted permanently.\n";
}
//detection level increment logic
void Logger::incrementDetectionLevel() {
    detectionLevel++;
    
    // Convert to string to store in your log file  for later use=age 
    string msg = "Detection level increased to: " + to_string(detectionLevel);
    
    // if the system crashed  Call your pipe-based log function to save it to disk
    log(msg); 

    // Immediate feedback to the user
    cout << "[ALERT] " << msg << endl;
}
