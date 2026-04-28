#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H
#include "SERVICE.h"
#include <string>
#include <iostream>
#include <unistd.h> // for sleep function in linux
#include <cstdlib>
#include <cstdio>
using namespace std;
class HTTPService:public Service{
    private:
    int requestCount;
    bool isHTTPS;
    public:

    //parameterized constructor
    HTTPService(int port,const string& type,const string& name,int requestCount,bool isHTTPS):Service(port,type,name),requestCount(requestCount),isHTTPS(isHTTPS){}
    //default constructor
    HTTPService():Service(){}
    //copy constructor
    HTTPService(const HTTPService& obj):Service(obj),requestCount(obj.requestCount),isHTTPS(obj.isHTTPS){}
    //setters in .cpp will be defined 
    void setRequestCount(int requestCount);
    void setIsHTTPS(bool isHTTPS);
    //getters will be defined in .cpp file
    int getRequestCount()const;
    bool getIsHTTPS()const;
    //methods of parent service  overrriden
    void execute() override {
    cout << "\n[INIT] Checking HTTPS Service Status..." << endl;

    #ifdef _WIN32
        // the sc query command is used in windows to search the servuce available in sys or not 
        int check = system("sc query w3svc >nul 2>&1"); // the real magic used after w3svc is that it will not print anything in screen it will just return a value 0 or not 


        if (check != 0) {
            // this will be then if the service is not found in system then it will ask user to install it or not
            char choice;
            cout << "[!] IIS Web Server not found. Do you want to install it? (y/n): ";
            cin >> choice;
                
            if (choice == 'y' || choice == 'Y') {
                cout << "[*] Launching Installer (Admin Rights Required) Please ensure u are using terminal in adminstrtor way ..." << endl;
                 //system cmmand used to fetc tge iis-websever 
                system("dism /online /enable-feature /featurename:IIS-WebServerRole /all");

            } else {
                //this logic is used to return back if user do not want to install the service
                cout << "[X] Installation cancelled by user. Returning..." << endl;
                return; //return used to abort the function 
            }
        }

        // if servuce is ready then start 
        cout << "[*] Starting HTTPS Service..." << endl;
        if (system("net start w3svc") == 0)//we are comparing the command if servuce is started then returbning value will be 0
         {
            isRunning = true; // 5. Update status
            cout << "[+] SUCCESS: HTTPS is now ACTIVE." << endl;
        } else {
            // error message if service is not started
            cout << "[!] ERROR: Failed to start. Try running as Administrator." << endl;
        }
cout<<"=====================================\n";
    #else
        // --- LINUX LOGIC ---
// Check if Apache2 is installed
        int check = system("dpkg -l | grep apache2 >/dev/null 2>&1");
        if (check != 0) {
            char choice;
            //USER WIILL CHOSE TO INSTALL OR NOT
            cout << "[!] Apache2 not found. Install now? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                //COMMAND IS SEECAGED FROM GOOGLE TO INSTALL APACHE2
                system("sudo apt-get update && sudo apt-get install -y apache2");
            } else {
                return;
            }
        }
        //SERVIEC START LOGIC 
        if (system("sudo systemctl start apache2") == 0) {
            isRunning = true;
            cout << "[+] SUCCESS: Apache2 is ACTIVE." << endl;
        }
        cout<<"========================================\n";
    #endif
}
     void stop() override {
    // if service runningbor not 
    if (!isRunning) {
        cout << "[!] HTTPS Service is already STOPPED." << endl;
        return;
    }

    cout << "\n[TERMINATING] Stopping HTTPS Web Service..." << endl;

    #ifdef _WIN32
        // 2. Windows command to stop IIS (w3svc) teken form google 
        // 'net stop' command servic ko stop 
        if (system("net stop w3svc") == 0) {
            isRunning = false;
            cout << "[-] SUCCESS: Windows IIS Service stopped." << endl;
        } else {
            cout << "[!] ERROR: Failed to stop Windows Service. (Admin rights check karein)" << endl;
        }

    #else
        // 3. Linux command to stop Apache2 serched from google 
        if (system("sudo systemctl stop apache2") == 0) {
            isRunning = false;
            cout << "[-] SUCCESS: Linux Apache Daemon stopped." << endl;
        } else {
            cout << "[!] ERROR: Failed to stop Linux Service." << endl;
        }
    #endif
}
void scan() override {
    string command;
    cout << "==================================\n";
    cout << "        SYSTEM SCANNING HTTPS      \n";
    cout << "===================================\n";
    
    #ifdef _WIN32
    // Windows par HTTPS (Port 443) check karne ki command
    cout << "[+] SCANNING ON WINDOWS (Port 443)\n";//port 443 is for https service
    // command for windows system to scan https service on port 443 and listening state seacrhed from google 
    command = "netstat -an | findstr \"LISTENING\" | findstr \":443\"";
    #else 
    // Linux par HTTPS check karne ki command
    cout << "[+] SCANNING ON LINUX (Port 443)\n";
    command = "netstat -an | grep LISTEN | grep :443";   
    #endif
//this pipe logic is used to execute the command in terminal and get the output in our program and then we can use that output to check if the service is running or not
    FILE* pipe = popen(command.c_str(), "r");// read only mode
    if (!pipe) {
        cout << "[!] Command execution error\n";
        return;
    }

    cout << "[+] SCANNING STARTED...\n";
    char buffer[128];
    bool found = false;
// gettiing output tis logic is used from c programming to read the output of command executed in terminal and then we are checking if there is any output that means service is running and listening on port 443
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {   
        found = true;
        cout << "[FOUND] " << buffer;
    }

    #ifdef _WIN32
    _sleep(300);
    #else 
    u_sleep(3000);
    #endif

    pclose(pipe);

    if (found) {
        cout << "[!] WARNING: HTTPS PORT (443) IS ACTIVE AND LISTENING\n";
    } else {
        cout << "[+] SYSTEM IS SAFE: No Web Service detected on Port 443\n";
    }

    cout << "=====================================\n";
}

//method of this class 
void injectPayloadSimulate();

};
    #endif 
