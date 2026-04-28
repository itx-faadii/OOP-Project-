#ifndef FIREWALL_H
#define FIREWALL_H    
#include"NETWORK.h"
#include <cstdio>
#include <list>
#include <string>
#include<iostream>      
using namespace std;
class Firewall:public NetworkNode{

    private:
    list<string> rules;
    string logFiles;
    public:
    //permeterized constructor
    Firewall(int id ,const string& name,const list<Service*> newService,const list<string> rules,const string& logFiles):
    NetworkNode(id,name,newService),rules(rules),logFiles(logFiles){}
    //copy constructor
    Firewall(const Firewall& obj)
    :NetworkNode(obj),rules(obj.rules),logFiles(obj.logFiles){}
    //default constructor   
    Firewall():NetworkNode(),rules(),logFiles(""){}
    //setters
    void setRules(const list<string> rules);
    void setLogFiles(const string& logFiles);
    //getters
    list<string> getRules()const;
    string getLogFiles()const;
    //methods
    void testVulnerability()override {
    cout << "--- Checking Windows Security ---" << endl;
    
    int result = system("netsh advfirewall show allprofiles state | findstr /i OFF");

    if (result == 0) {
        cout << "ALERT: Your Firewall is OFF! (Vulnerability Found)" << endl;
    } else {
        cout << "SUCCESS: Firewall is ON." << endl;
    }
}
 void checkDataFlow() override {
        cout<<"[+]  Checking data flow in Firewall....\n";
        cout<<"====================================\n";
        cout<<"[+] Data flow check in progress...\n";   
        cout<<"[+] Analyzing network traffic...\n";
        cout<<"====================================\n";
        
        string destinantion;
        cout<<"Enter the destination IP address or domain name: ";
        cin.ignore();
        getline(cin, destinantion);
        
        string command;
        #ifdef _WIN32
            cout<<"[DETECTED OS] Windows\n";
            cout<<"[*] Using Windows Terminal for data flow check...\n";
            command ="tracert " + destinantion;
        #else
            cout<<"[DETECTED OS] Linux\n";
            cout<<"[*] Using Linux Terminal for data flow check...\n";
            command ="traceroute " + destinantion;
        #endif
        
        cout<<"[*] Running command: " << command << "\n";
        cout<<"====================================\n";
        FILE* pipe=popen(command.c_str(),"r");
        if(!pipe){  
            cout<<"! ERROR: Failed to run command\n";
            return ;
        }
        char buffer[512];
        while(fgets(buffer,sizeof(buffer),pipe)!=nullptr){
            cout<<buffer;
        }
        pclose(pipe);
        cout<<"====================================\n";
        cout<<"[+] Data flow checked successfully \n";
    }
 void scanSystem() override {
    int choose;
    cout << "================================\n";
    cout << "       SCANNING FIREWALL        \n";
    cout << "================================\n"; 
    cout << "ENTER YOUR CHOICE \n";
    cout << "1. For checking ports\n";
    cout << "2. For checking tasklists\n";
    cout << "3. For IP scan\n";
    cout << "4. For Configuration scan\n";
    cin >> choose;
    cin.ignore();

    string command = "";

    switch (choose) {
        case 1: // Port Scan
            #ifdef _WIN32
                command = "netstat -an | findstr \"LISTENING\"";
            #else
                command = "netstat -an | grep \"LISTEN\"";
            #endif
            break;

        case 2: // Tasklist
            #ifdef _WIN32
                command = "tasklist";
            #else
                command = "ps -aux";
            #endif
            break;

        case 3: // IP Scan
            #ifdef _WIN32
                command = "ipconfig /all";
            #else
                command = "ip -a addr || ifconfig -a";
            #endif
            break;

        case 4: // Configuration Scan
            #ifdef _WIN32
                command = "systeminfo";
            #else
                command = "uname -a";
            #endif
            break;

        default:
            cout << "Invalid choice\n";
            return;
    }

    if (command.empty()) {
        cout << "[!] ERROR: Command not set.\n";
        return;
    }

    cout << "[DETECTED OS] ";
    #ifdef _WIN32 
        cout << "Windows" << endl;
    #else 
        cout << "Linux" << endl;
    #endif 

    cout << "[*] Running command: " << command << endl;
    cout << "================================\n";
    
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cout << "[!] ERROR: Failed to run command\n";
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        cout << buffer;
    }
    pclose(pipe);

    cout << "================================\n";
    cout << "Scan completed successfully\n";
}

void logTraffic(const string& trafficInfo);
void allowTraffic(const string& rule);
void blockTraffic(const string& rule);
void updateRules(const list<string>& newRules);

};
#endif
